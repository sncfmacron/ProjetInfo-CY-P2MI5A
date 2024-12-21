#!/bin/bash


# c-wire.sh : shell script to compile program_c and sort data


# Error code declaration

ERR_INVALID_PARAMETER=100
ERR_FILE_MISSING=101
ERR_INVALID_FILTER=102
ERR_COMPILATION=103

# Directories declaration

DIR_EXTRACTED_STATION="tmp/extracted_station.csv"       # Temporary file to store extracted stations
DIR_EXTRACTED_CONSUMER="tmp/extracted_consumer.csv"     # Temporary file to store extracted consumers
DIR_GNUPLOT_PROGRAM="gnuplot_LVminmax.gp"               # Path to the Gnuplot program
DIR_LV_MIN_MAX="output/lv_all_minmax.csv"               # Path to the file used to make graphs

# Variable declaration to define the text color and appearance in the terminal

bold=$(tput bold)
normal=$(tput sgr0)
underline='\e[4m'

yellow='\033[1;33m'
red='\033[1;31m'
darkred='\033[0;31m'
blue='\033[1;36m'
normalColor='\033[0m'


# Display the c-wire help manual
displayHelp() {
    echo "${bold} NAME ${normal}"
    echo "      c-wire - Data managing"
    echo
    echo "${bold} DESCRIPTION ${normal}"
    echo "      This program processes data for an electricity distribution."
    echo
    echo "${bold} SYNOPSIS ${normal}"
    echo -e "      $0 [${underline}FILE_PATH.csv${normal}] [${underline}STATION_TYPE${normal}] [${underline}CONSUMER_TYPE${normal}] [${underline}POWER_PLANT_ID${normal}] ..."
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
    exit 0
}

# Display the reduced c-wire help manual
displayMiniHelp() {
    echo
    echo "Usage: $0 [FILE_PATH.csv] [STATION_TYPE] [CONSUMER_TYPE] [POWER_PLANT_ID] ..."
    echo "Use ${bold}-h${normal} option for full help."
    exit "$ERR_INVALID_PARAMETER"
}

# Display the program version
displayVersion () {
    echo "c-wire ${bold}v1.6.0${normal}"
    echo "Written by Nathan Choupin, Romain Michaut-Joyeux and Guirec Vetier | MI5-A group." 
    exit 0
}

# Verify the presence of the specified file, exit the program if the file is missing
verifyFilePresence () {
    filePath="$1"
    if [[ ! -f "$filePath" ]]; then
        echo "${bold}[ERROR]${normal} File $filePath is missing."
        exit "$ERR_FILE_MISSING"
    fi
}

# Validate parameters to run the program, exit the program if the parameters are invalid
verifyParameters() {
    # Check if "-h" is present
    for option in "$@"; do
        case $option in
            -h) 
                displayHelp
            ;;
        esac
    done

    # Check if "--version" is present
    for option in "$@"; do
        case $option in
            --version) 
                displayVersion
            ;;
        esac
    done

    # Verify the number of parameters
    if [[ $# -gt 5 ]] || [[ $# -lt 1 ]]; then
        echo -e "[${darkred}WARNING${normal}] You must provide at least the path to your input file, the station type and the consumer type."
        displayMiniHelp
    fi

    # Verify the first parameter
    if [[ ! -f "$1" ]]; then
        echo -e "[${darkred}WARNING${normal}] The first option must indicate a path to a valid '.csv' file."
        displayMiniHelp
    fi

    # Verify the second parameter
    case "$2" in
        hva|hvb|lv)
            ;;
        *)
            echo -e "[${darkred}WARNING${normal}] Second option must be ${red}hva${normal}, ${red}hvb${normal}, or ${red}lv${normal}."
            displayMiniHelp
            ;;
    esac

    # Verify the third parameter
    case "$3" in
        comp|indiv|all)
            # Prevent invalid combinations
            if [[ "$2" == "hvb" && "$3" == "all" ]] || [[ "$2" == "hvb" && "$3" == "indiv" ]] || [[ "$2" == "hva" && "$3" == "all" ]] || [[ "$2" == "hva" && "$3" == "indiv" ]]; then
                echo -e "[${darkred}WARNING${normal}] The following combinations are forbidden: ${red}hvb all${normal}, ${red}hvb indiv${normal}, ${red}hva all${normal}, and ${red}hva indiv${normal}."
                displayMiniHelp
            fi
            ;;
        *)
            echo -e "[${darkred}WARNING${normal}] The third option must be ${red}comp${normal}, ${red}indiv${normal}, or ${red}all${normal}."
            displayMiniHelp
            ;;
    esac

    # Verify the fourth parameter if it is provided (valid power plant identifier)
    # The grep command checks if the identifier exists in the first column of the input file
    if [ -n "$4" ]; then
        if ! grep -q "^$4;" "$1"; then
            echo -e "$[${darkred}WARNING${normal}] '"$4"' is not a valid power plant identifier."
            displayMiniHelp
        fi
    fi
}

# Clean temporary folder before and after program execution
cleanFolders () {
    rm -rf tmp/*
}

# Set up directories for program execution
processFolders () {
    cleanFolders

    # These folders are created if they don't exist. If they exist, nothing happens
    mkdir -p graphs input tmp output
}

# Start the C program compilation using make to automate the build process
compilation () {
    # Start compilation only if the executable program is absent
    if [[ ! -f codeC/program_c ]]; then
        echo -e "${bold}[INFO]${normal} ${yellow}program_c${normal} is absent, compilation is executed."
        echo
        
        # '--no-print-directory' option is used to avoid make sending information messages when browsing files.
        make  --no-print-directory -C codeC
        
        # Check that compilation has been completed successfully and stop the program if necessary
        if [[ $? -ne 0 ]]; then
            echo "${bold}[ERROR]${normal} Compilation error."
            exit "$ERR_COMPILATION"
        fi
    fi
}

# Display the execution time of a function with a precision of two decimal
# date command gives the nanoseconds elapsed since 01/01/1970
displayTime() {
    local timeMsg="$1"
    local startTime="$2"
    local endTime=$(date +%s%N)

    local elapsedTime=$((endTime - startTime))

    # Converting nanoseconds into seconds and milliseconds
    local seconds=$((elapsedTime / 1000000000))
    local milliseconds=$(((elapsedTime % 1000000000) / 1000000))

    echo
    echo -e "${timeMsg} in $seconds.${milliseconds:1:3}s."
}

# Create two filters for consumers and stations to extract only the data required for the user's requested analysis
# We added a condition that checks if the user has specified a power plant plant id or not
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

    # Exit the program if the filter is empty
    if [[ "$filter" == "" ]]; then
        echo "${bold}[ERROR]${normal} Data filter creation failed."
        exit "$ERR_INVALID_FILTER"
    fi
}

# Count the number of lines in the sorted file. This will be useful for allocating memory in the C program
stationCount () {
    verifyFilePresence "$DIR_EXTRACTED_STATION"
    stationNumber=$(wc -l < "$DIR_EXTRACTED_STATION")
}

# Sort relevant data from input file
sortingData () {
    # We use awk to extract and write data in two temporary '.csv' files, read by the C program for processing
    # Options in awk line : -F to indicate the separating character and -v to indicate a variable

    local startTime=$(date +%s%N)

    inputFilePath="$1"
    stationType="$2"
    consumerType="$3"
    powerPlantID="$4"

    echo
    echo -e "Starting data processing for station type ${red}$stationType${normalColor} and consumer type ${red}$consumerType${normalColor}..."

    # Creating filters to extract only relevant informations
    awkFilter "$@"

    # Redirecting to /dev/null prevents standard output from appearing and keeps terminal clean
    awk -F ';' -v custom_id="$powerPlantID" -v stationFile="$DIR_EXTRACTED_STATION" -v consumerFile="$DIR_EXTRACTED_CONSUMER" "$filter" "$inputFilePath" > /dev/null

    # Check if the extraction and the writing has been completed successfully
    verifyFilePresence "$DIR_EXTRACTED_STATION"

    verifyFilePresence "$DIR_EXTRACTED_STATION"

    displayTime "...1. ${blue}"$1"${normal} extracted" "$startTime"

    stationCount

    # We run the C program with the useful parameters
    codeC/program_c $stationType $consumerType $stationNumber $powerPlantID
}

# Create graphs using output files in case of "lv all" analysis
makeGraphs () {
    verifyFilePresence "$DIR_GNUPLOT_PROGRAM"

    local filePath="$1"
    local stationType="$2"
    local consumerType="$3"
    local startTime=$(date +%s%N)

    # Check if the user has typed "lv all" and verify that gnuplot is present on the user's computer
    if [[ "$stationType" == "lv" && "$consumerType" == "all" ]]; then
        if ! command -v gnuplot &>/dev/null; then
            echo
            echo -e "[${darkred}WARNING${normal}] Gnuplot is not installed. Type ${yellow}sudo apt install gnuplot${normal} to install it."

        elif [[ ! -f "$DIR_LV_MIN_MAX" ]]; then
            echo
            echo -e "[${darkred}WARNING${normal}] File $DIR_LV_MIN_MAX not found : skipping graph creation..."
            
        else
            echo
            echo "Making graphs..."

            # Start Gnuplot program
            gnuplot gnuplot_LVminmax.gp

            # Checks that gnuplot program has been completed successfully
            if [[ $? -ne 0 ]]; then
                echo "${bold}[ERROR]${normal} Gnuplot error: see program output for more information."
            else
                displayTime "...3. Graphs has been created in ${blue}./graphs${normal}" "$startTime"
            fi
        fi
    fi
}

# Main function: calls all functions
runProgram () {

    echo

    verifyParameters "$@"

    processFolders

    compilation

    # Start processing data
    startTime=$(date +%s%N)

    sortingData "$@"
    
    makeGraphs "$1" "$2" "$3"

    cleanFolders

    echo
    displayTime "Program completed successfully" "$startTime"

    exit 0
}

runProgram "$@"