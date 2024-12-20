#!/bin/bash


# Shell script to compile program_c and sort data


# Error code declaration

ERR_INVALID_PARAMETER=100
ERR_INVALID_FILTER=101
ERR_FILE_MISSING=102
ERR_FILE_CREATION=103
ERR_COMPILATION=104
PROGRAM_ABORTED=105
PROGRAM_NOT_FOUND=106

# Directories declaration

DIR_EXTRACTED_STATION="tmp/extracted_station.csv"
DIR_EXTRACTED_CONSUMER="tmp/extracted_consumer.csv"
DIR_GNUPLOT_PROGRAM="gnuplot_LVminmax.gp"
DIR_LVMINMAX="output/lv_all_minmax.csv"

# Variable declaration to set the text in bold or in red using 'tput'

bold=$(tput bold)
normal=$(tput sgr0)
yellow='\033[1;33m'
red='\033[1;31m'
darkred='\033[0;31m'
blue='\033[1;36m'
normalColor='\033[0m'


# Displays the program help manual
display_help() {
    # We use 'tput' to set the text in bold to make the text more aesthetic

    echo "${bold} NAME ${normal}"
    echo "      c-wire - data managing"
    echo
    echo "${bold} DESCRIPTION ${normal}"
    echo "      This program processes data for an electricity distribution."
    echo
    echo "${bold} SYNOPSIS ${normal}"
    echo "      $0 [FILE_PATH.csv] [STATION_TYPE] [CONSUMER_TYPE] [POWER_PLANT_ID] ..."
    echo
    echo "${bold} OPTIONS ${normal}"
    echo "     ${bold} [FILE_PATH.csv] ${normal}  Location of the input file (required)"
    echo
    echo "     ${bold} [STATION_TYPE] ${normal}   Type of station to process: 'hva', 'hvb' or 'lv' (required)"
    echo
    echo "     ${bold} [CONSUMER_TYPE] ${normal}  Type of consumer to process: 'all', 'comp' or 'indiv' (required)"
    echo
    echo "     ${bold} [POWER_PLANT_ID] ${normal} Filters the results for a specific power plant ID (optional)"
    echo
    echo "     ${bold} -h ${normal}               Displays help manual"
    echo
    echo "     ${bold} --version ${normal}        Displays program version"
    echo
    echo "${bold} WARNING ${normal}"
    echo "      The following combinations are forbidden:"
    echo "      * hvb all"
    echo "      * hvb indiv"
    echo "      * hva all"
    echo "      * hva indiv"
    echo
    echo "${bold} EXAMPLE ${normal}"
    echo "      $0 input/DATA_CWIRE.csv lv comp 3"
    echo
    exit 0
}

# Displays reduced program help
display_mini_help() {
    echo "Usage: $0 [path_file.csv] [station_type] [consumer_type] [power_plant_id]"
    echo "Use -h parameter to get full help."
    exit "$ERR_INVALID_PARAMETER"
}

# Verifies the presence of a file
verifyFilePresence () {
    filePath="$1"
    if [[ ! -f "$filePath" ]]; then
        echo "${bold}[ERROR]${normal} File $filePath is missing."
        exit "$ERR_FILE_MISSING"
    fi
}

# Displays the program version
displayVersion () {
    echo "c-wire ${bold}v1.6.0${normal}"
    echo "Written by Nathan Choupin, Romain Michaut-Joyeux and Guirec Vetier." 
    exit 0
}

# Parameters verification
verifyParameters() {
    # Verifies if "-h" is present
    for option in "$@"; do
        case $option in
            -h) 
                display_help
            ;;
        esac
    done

    # Verifies if "--version" is present
    for option in "$@"; do
        case $option in
            --version) 
                displayVersion
            ;;
        esac
    done

    # Verifying number of parameters
    if [[ $# -gt 5 ]] || [[ $# -lt 1 ]]; then
        echo -e "[${darkred}WARNING${normal}] You must provide at least the path to your input file, the station type and the consumer type."
        display_mini_help
    fi

    # Verifying first parameter
    if [[ ! -f "$1" ]]; then
        echo -e "[${darkred}WARNING${normal}] The first option must indicate a path to a valid '.csv' file."
        display_mini_help
    fi

    # Verifying second parameter
    case "$2" in
        hva|hvb|lv)
            ;;
        *)
            echo -e "[${darkred}WARNING${normal}] Second option must be ${red}hva${normal}, ${red}hvb${normal}, or ${red}lv${normal}."
            display_mini_help
            ;;
    esac

    # Verifying third parameter
    case "$3" in
        comp|indiv|all)
            # Preventing invalid combinations
            if [[ "$2" == "hvb" && "$3" == "all" ]] || [[ "$2" == "hvb" && "$3" == "indiv" ]] || [[ "$2" == "hva" && "$3" == "all" ]] || [[ "$2" == "hva" && "$3" == "indiv" ]]; then
                echo -e "[${darkred}WARNING${normal}] The following combinations are forbidden: ${red}hvb all${normal}, ${red}hvb indiv${normal}, ${red}hva all${normal}, and ${red}hva indiv${normal}."
                display_mini_help
            fi
            ;;
        *)
            echo -e "[${darkred}WARNING${normal}] The third option must be ${red}comp${normal}, ${red}indiv${normal}, or ${red}all${normal}."
            display_mini_help
            ;;
    esac

    # Verifying fourth parameter (valid powerplant identifier)
    # 'grep' checks if the id exists in input file
    if [ -n "$4" ]; then
        if ! grep -q "^$4;" "$1"; then
            echo -e "[${darkred}WARNING${normal}] The fourth option must be a valid power plant identifier."
            display_mini_help
        fi
    fi
}

# Clean folders and unused file
cleanFolders () {
    rm -rf tmp/*
}

# Prepares directories for program execution
processFolders () {
    cleanFolders

    # These folders are created if they don't exist. If they exist, nothing happens
    mkdir -p graphs input tmp output
}

# Starts program_c compilation using 'make'
compilation () {
    # Compile if the program is absent
    if [[ ! -f codeC/program_c ]]; then
        echo -e "${bold}[INFO]${normal} ${yellow}program_c${normal} is absent, compilation is executed."
        echo
        
        # --no-print-directory option is used to avoid 'make' sending messages when browsing files.
        make  --no-print-directory -C codeC
        
        # Checks that compilation has gone well
        if [[ $? -ne 0 ]]; then
            echo "${bold}[ERROR]${normal} Compilation error."
            exit "$ERR_COMPILATION"
        fi
    fi
}

# Displays the execution time of a function
displayTime() {
    local timeMsg="$1"
    local startTime="$2"
    local endTime=$(date +%s%N)

    local elapsedTime=$((endTime - startTime))

    local seconds=$((elapsedTime / 1000000000))
    local milliseconds=$(((elapsedTime % 1000000000) / 1000000))

    echo
    echo -e "${timeMsg} in $seconds.${milliseconds:1:3}s."
}

# Produces the data filter corresponding to the request
awkFilter () {
    case "$2" in
        hvb) 
            filter='
            NR > 1 && (custom_id == "" || $1 == custom_id) && $2 != "-" && $3 == "-" && $7 != "-" { print $2, $7 > stationFile }
            NR > 1 && (custom_id == "" || $1 == custom_id) && $2 != "-" && $3 == "-" && $8 != "-" { print $2, $8 > consumerFile }
            '
            ;;
        hva)
            filter='
            NR > 1 && (custom_id == "" || $1 == custom_id) && $3 != "-" && $4 == "-" && $7 != "-" { print $3, $7 > stationFile }
            NR > 1 && (custom_id == "" || $1 == custom_id) && $3 != "-" && $4 == "-" && $8 != "-" { print $3, $8 > consumerFile }
            '
            ;;
        lv)
            case "$3" in
                all)
                    filter='
                    NR > 1 && (custom_id == "" || $1 == custom_id) && $4 != "-" && $7 != "-" { print $4, $7 > stationFile }
                    NR > 1 && (custom_id == "" || $1 == custom_id) && $4 != "-" && $8 != "-" { print $4, $8 > consumerFile }
                    '
                    ;;
                comp)
                    filter='
                    NR > 1 && (custom_id == "" || $1 == custom_id) && $4 != "-" && $7 != "-" { print $4, $7 > stationFile }
                    NR > 1 && (custom_id == "" || $1 == custom_id) && $4 != "-" && $6 == "-" && $8 != "-" { print $4, $8 > consumerFile }
                    '
                    ;;
                indiv)
                    filter='
                    NR > 1 && (custom_id == "" || $1 == custom_id) && $4 != "-" && $7 != "-" { print $4, $7 > stationFile }
                    NR > 1 && (custom_id == "" || $1 == custom_id) && $4 != "-" && $5 == "-" && $8 != "-" { print $4, $8 > consumerFile }
                    '
                    ;;
            esac
                ;;
    esac

    if [[ "$filter" == "" ]]; then
        echo "${bold}[ERROR]${normal} Data filter creation failed."
        exit "$ERR_INVALID_FILTER"
    fi
}

# Count the number of lines in the sorted file
stationCount () {
    verifyFilePresence "$DIR_EXTRACTED_STATION"
    stationNumber=$(wc -l < "$DIR_EXTRACTED_STATION")
}

# Sorting data function
sortingData () {
    # We use 'awk' to sort data in temporary '.csv' files, read by program_c and filters only relevant informations.
    # Options in 'awk' line : -F to indicate separating character, -v to indicate a variable.

    # 'date' command gives the elapsed seconds since 01/01/1970.

    local startTime=$(date +%s%N)

    inputFilePath="$1"
    stationType="$2"
    consumerType="$3"
    powerPlantID="$4"

    echo
    echo -e "Starting data processing for station type ${red}$stationType${normalColor} and consumer type ${red}$consumerType${normalColor}..."

    awkFilter "$@"

    awk -F ';' -v custom_id="$powerPlantID" -v stationFile="$DIR_EXTRACTED_STATION" -v consumerFile="$DIR_EXTRACTED_CONSUMER" "$filter" "$inputFilePath" > /dev/null

    verifyFilePresence "$DIR_EXTRACTED_STATION"

    verifyFilePresence "$DIR_EXTRACTED_STATION"

    displayTime "...1. ${blue}"$1"${normal} extracted" "$startTime"

    stationCount

    codeC/program_c $stationType $consumerType $stationNumber $powerPlantID
}


getMaxLoad () {
    maxLoad=$(tail -n 1 "$DIR_LVMINMAX" | awk -F ':' '{print $3}')
}

# Function to make graphs using output files
makeGraphs () {
    local filePath="$1"
    local stationType="$2"
    local consumerType="$3"
    local startTime=$(date +%s%N)

    if [[ "$stationType" == "lv" && "$consumerType" == "all" ]]; then
        if ! command -v gnuplot &>/dev/null; then
            echo
            echo -e "[${darkred}WARNING${normal}] Gnuplot is not installed. Type ${yellow}sudo apt install gnuplot${normal} to install it."

        elif [[ ! -f "$DIR_LVMINMAX" ]]; then
            echo
            echo -e "[${darkred}WARNING${normal}] File $DIR_LVMINMAX not found : skipping graph creation..."
            exit "$PROGRAM_NOT_FOUND"

        else
            verifyFilePresence "$DIR_GNUPLOT_PROGRAM"
            echo
            echo "Making graphs..."

            getMaxLoad

            gnuplot -e "maxLoad=${maxLoad}" gnuplot_LVminmax.gp

            # Checks that gnuplot program has gone well
            if [[ $? -ne 0 ]]; then
                echo "${bold}[ERROR]${normal} Gnuplot error."
            else
                displayTime "...3. The graph has been created in ${blue}./graphs${normal}" "$startTime"
            fi
        fi
    fi
}

# Functions calls
runProgram () {

    echo

    verifyParameters "$@"

    processFolders

    compilation

    # Start processing
    startTime=$(date +%s%N)

    sortingData "$@"
    
    makeGraphs "$1" "$2" "$3"

    cleanFolders

    echo
    displayTime "Program completed successfully" "$startTime"

    exit 0
}

runProgram "$@"