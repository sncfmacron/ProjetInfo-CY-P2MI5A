#!/bin/bash


# Shell script to compile program_c and sort data


# Error code declaration
ERR_INVALID_PARAMETER=100
ERR_INVALID_FILTER=101
ERR_FILE_MISSING=102
ERR_FILE_CREATION=103
ERR_COMPILATION=104
PROGRAM_ABORTED=105


# Variable declaration to set the text in bold using 'tput'
bold=$(tput bold)
normal=$(tput sgr0)


# Displays the program help manual
display_help() {
    # We use 'tput' to set the text in bold to make the text more aesthetic

    echo "${bold} NAME ${normal}"
    echo "      c-wire - data managing"
    echo ""
    echo "${bold} DESCRIPTION ${normal}"
    echo "      This program processes data for an electricity distribution."
    echo ""
    echo "${bold} SYNOPSIS ${normal}"
    echo "      ./c-wire.sh [file_path.csv] [station_type] [consumer_type] [power_plant_id]"
    echo ""
    echo "${bold} OPTIONS ${normal}"
    echo "     ${bold} [file_path.csv] ${normal}  Location of the input file (required)"
    echo "     ${bold} [station_type] ${normal}   Type of station to process: 'hva', 'hvb' or 'lv' (required)"
    echo "     ${bold} [consumer_type] ${normal}  Type of consumer to process: 'all', 'comp' or 'indiv' (required)"
    echo "     ${bold} [power_plant_id] ${normal} Filters the results for a specific power plant ID (optional)"
    echo ""
    echo "     ${bold} -h ${normal}               Displays help manual"
    echo ""
    echo "${bold} WARNING ${normal}"
    echo "      The following combinations are forbidden:"
    echo "      * hvb all"
    echo "      * hvb indiv"
    echo "      * hva all"
    echo "      * hva indiv"
    echo ""
    echo "${bold} EXAMPLE ${normal}"
    echo "      ./c-wire.sh input/DATA_CWIRE.csv lv comp 3"
    echo ""
    exit 0
}


# Displays reduced program help
display_mini_help() {
    echo ""
    echo "Usage: ./c-wire.sh [path_file.csv] [station_type] [consumer_type] [power_plant_id]"
    echo "Use ${bold}-h${normal} parameter to get full help."
    exit "$ERR_INVALID_PARAMETER"
}


# Verifies the presence of a file
verifyFilePresence () {
    filePath="$1"
    if [[ ! -f "$filePath" ]]; then
        echo "ERROR: File $filePath is missing."
        exit "$ERR_FILE_MISSING"
    fi
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

    # Verifying number of parameters
    if [[ $# -gt 5 ]] || [[ $# -lt 1 ]]; then
        echo "You must provide at least the path to your input file, the station type and the consumer type."
        display_mini_help
    fi

    # Verifying first parameter
    if [[ ! -f "$1" ]]; then
        echo "The first option must indicate a path to a valid '.csv' file."
        display_mini_help
    fi

    # Verifying second parameter
    case "$2" in
        hva|hvb|lv)
            ;;
        *)
            echo "Second option must be 'hva', 'hvb', or 'lv'."
            display_mini_help
            ;;
    esac

    # Verifying third parameter
    case "$3" in
        comp|indiv|all)
            # Preventing invalid combinations
            if [[ "$2" == "hvb" && "$3" == "all" ]] || [[ "$2" == "hvb" && "$3" == "indiv" ]] || [[ "$2" == "hva" && "$3" == "all" ]] || [[ "$2" == "hva" && "$3" == "indiv" ]]; then
                echo "The following combinations are forbidden: 'hvb all', 'hvb indiv', 'hva all', and 'hva indiv'."
                display_mini_help
            fi
            ;;
        *)
            echo "The third option must be 'comp', 'indiv', or 'all'."
            display_mini_help
            ;;
    esac

    # Verifying fourth parameter (valid powerplant identifier)
    # 'grep' checks if the id exists in input file
    if [ -n "$4" ]; then
        if ! grep -q "^$4;" "$1"; then
            echo "The fourth option must be a valid power plant identifier."
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
    # At this stage, program_c doesn't exist because we've verified it in 'processFolders'

    local stationType="$1"
    local consumerType="$2"
    local powerPlantID="$3"
    # Compile if the program is absent
    if [[ ! -f codeC/program_c ]]; then
        echo "[INFO] 'program_c' is absent, compilation is executed."
        
        # --no-print-directory option is used to avoid 'make' sending messages when browsing files.
        make  --no-print-directory -C codeC
        
        # Checks that compilation has gone well
        if [[ $? -ne 0 ]]; then
            echo "ERROR : Compilation error."
            exit "$ERR_COMPILATION"
        fi
    fi
    
}


# Displays the execution time of a function
displayTime() {
    local timeMsg="$1"
    local startTime="$2"
    local endTime="$3"

    local elapsedTime=$((endTime - startTime))

    local seconds=$((elapsedTime / 1000000000))
    local milliseconds=$(((elapsedTime % 1000000000) / 1000000))

    echo ""
    echo "[INFO] ${timeMsg} in $seconds.${milliseconds:1:3} seconds."
    echo ""
}


# Produces the data filter corresponding to the request
awkFilter () {
    case "$2" in
        hvb)
            filter='
            NR > 1 && (custom_id == "" || $1 == custom_id) && $2 != "-" && $3 == "-" && $7 != "-" { print $2, $7 > "tmp/station_sorted.csv" }
            NR > 1 && (custom_id == "" || $1 == custom_id) && $2 != "-" && $3 == "-" && $8 != "-" { print $2, $8 > "tmp/consumer_sorted.csv" }
            '
            ;;
        hva)
            filter='
            NR > 1 && (custom_id == "" || $1 == custom_id) && $3 != "-" && $4 == "-" && $7 != "-" { print $3, $7 > "tmp/station_sorted.csv" }
            NR > 1 && (custom_id == "" || $1 == custom_id) && $3 != "-" && $4 == "-" && $8 != "-" { print $3, $8 > "tmp/consumer_sorted.csv" }
            '
            ;;
        lv)
            case "$3" in
                all)
                    filter='
                    NR > 1 && (custom_id == "" || $1 == custom_id) && $4 != "-" && $7 != "-" { print $4, $7 > "tmp/station_sorted.csv" }
                    NR > 1 && (custom_id == "" || $1 == custom_id) && $4 != "-" && $8 != "-" { print $4, $8 > "tmp/consumer_sorted.csv" }
                    '
                    ;;
                comp)
                    filter='
                    NR > 1 && (custom_id == "" || $1 == custom_id) && $4 != "-" && $7 != "-" { print $4, $7 > "tmp/station_sorted.csv" }
                    NR > 1 && (custom_id == "" || $1 == custom_id) && $4 != "-" && $6 == "-" && $8 != "-" { print $4, $8 > "tmp/consumer_sorted.csv" }
                    '
                    ;;
                indiv)
                    filter='
                    NR > 1 && (custom_id == "" || $1 == custom_id) && $4 != "-" && $7 != "-" { print $4, $7 > "tmp/station_sorted.csv"}
                    NR > 1 && (custom_id == "" || $1 == custom_id) && $4 != "-" && $5 == "-" && $8 != "-" { print $4, $8 > "tmp/consumer_sorted.csv"}
                    '
                    ;;
            esac
                ;;
    esac

    if [[ "$filter" == "" ]]; then
        echo "ERROR: Data filter creation failed."
        exit "$ERR_INVALID_FILTER"
    fi
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

    echo "Starting data processing for station type '$stationType' and consumer type '$consumerType'..."

    awkFilter "$@"

    awk -F ';' -v custom_id="$powerPlantID" "$filter" "$inputFilePath" > /dev/null

    verifyFilePresence "tmp/station_sorted.csv"

    verifyFilePresence "tmp/consumer_sorted.csv"

    local endTime=$(date +%s%N)
    local timeMsg="$inputFilePath sorted"
    displayTime "$timeMsg" "$startTime" "$endTime"
}


# Count the number of lines in the sorted file
stationCount () {
    verifyFilePresence "tmp/station_sorted.csv"
    stationNumber=$(wc -l < tmp/station_sorted.csv)
}


# Function to make graphs using output files
makeGraphs () {
    local stationType="$1"
    local consumerType="$2"

    if [[ "$1" == "lv" && "$2" == "all" ]]; then
       if ! command -v gnuplot &>/dev/null; then
            echo "Gnuplot is not installed. Use 'sudo apt install gnuplot' to install it."
            exit 1
        else
            verifyFilePresence "gnuplot_LVminmax.gp"
            echo ""
            echo "Making graphs..."

            gnuplot gnuplot_LVminmax.gp

            echo ""
            echo "[INFO] The graph has been successfully created in './graphs'."
        fi
    fi
}


# Functions calls
runProgram () {
    verifyParameters "$@"

    processFolders

    compilation "$2" "$3" "$4" "$stationNumber"

    # Start processing
    startTime=$(date +%s%N)

    sortingData "$@"

    stationCount

    local endTime=$(date +%s%N)
    local timeMsg="Program completed successfully"
    displayTime "$timeMsg" "$startTime" "$endTime"
    

    makeGraphs "$2" "$3"

    local endTime=$(date +%s%N)
    local timeMsg="Program completed successfully with Graphs"
    displayTime "$timeMsg" "$startTime" "$endTime"
    exit 0
}


runProgram "$@"