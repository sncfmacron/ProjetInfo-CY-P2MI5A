#!/bin/bash


# Shell script to compile program_c and sort data


# Displays the program help manual
display_help() {
    # We use 'tput' to set the text in bold to make the text more aesthetic
    bold=$(tput bold)
    normal=$(tput sgr0)

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
    bold=$(tput bold)
    normal=$(tput sgr0)
    echo ""
    echo "${bold}Usage${normal}: ./c-wire.sh [path_file.csv] [station_type] [consumer_type] [power_plant_id]"
    echo "Use -h parameter to get full help."
    exit 1
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
    rm -rf temp/*
}


# Prepares directories for program execution
processFolders () {
    cleanFolders

    # These folders are created if they don't exist. If they exist, nothing happens
    mkdir -p graphs input temp output

    if [[ -f codeC/program_c ]]; then
        echo "INFO: 'program_c' is already present, compilation is not executed."
        echo ""
        exit 3
    fi
}


# Starts program_c compilation using 'make'
compilation () {
    # At this stage, program_c doesn't exist because we've verified it in 'processFolders'

    local stationType="$1"
    local consumerType="$2"
    local stationID="$3"
    # --no-print-directory option is used to avoid 'make' sending messages when browsing files.
    make --no-print-directory -C codeC run ARGS="$stationType $consumerType $stationID $stationNumber"

    # Checks that compilation has gone well
    if [[ $? -ne 0 ]]; then
        echo "ERROR : compilation error."
        exit 2
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
    echo "---- ${timeMsg} in $seconds.${milliseconds} seconds ----"
    echo ""
}


# Sorting data function
sortingData () {

    # We use 'awk' to sort data in temporary '.csv' files, read by program_c and filters only relevant informations.
    # Options in 'awk' line : -F to indicate separating character, -v to indicate a variable.

    # 'date' command gives the elapsed seconds since 01/01/1970.

    startTime=$(date +%s%N)

    local filePath="$1"
    local stationType="$2"
    local consumerType="$3"
    local powerPlantID="$4"

    case "$2" in
        hvb)
            filter='
            NR > 1 && (custom_id == "" || $1 == custom_id) && $2 != "-" && $3 == "-" && $7 != "-" { print $2, $7 > "temp/station_sorted.csv" }
            NR > 1 && (custom_id == "" || $1 == custom_id) && $2 != "-" && $3 == "-" && $8 != "-" { print $2, $8 > "temp/consumer_sorted.csv" }
            '
            ;;
        hva)
            filter='
            NR > 1 && (custom_id == "" || $1 == custom_id) && $3 != "-" && $4 == "-" && $7 != "-" { print $3, $7 > "temp/station_sorted.csv" }
            NR > 1 && (custom_id == "" || $1 == custom_id) && $3 != "-" && $4 == "-" && $8 != "-" { print $3, $8 > "temp/consumer_sorted.csv" }
            '
            ;;
        lv)
            case "$3" in
                all)
                    filter='
                    NR > 1 && (custom_id == "" || $1 == custom_id) && $4 != "-" && $7 != "-" && $4 != "LV Station" { print $4, $7 > "temp/station_sorted.csv" }
                    NR > 1 && (custom_id == "" || $1 == custom_id) && $4 != "-" && $8 != "-" && $4 != "LV Station" { print $4, $8 > "temp/consumer_sorted.csv" }
                    '
                    ;;
                comp)
                    filter='
                    NR > 1 && (custom_id == "" || $1 == custom_id) && $4 != "-" && $7 == "-" { print $4, $7 }
                    NR > 1 && (custom_id == "" || $1 == custom_id) && $4 != "-" && $6 == "-" && $8 != "-" { print $4, $8 }
                    '
                    ;;
                indiv)
                    filter='
                    NR > 1 && (custom_id == "" || $1 == custom_id) && $4 != "-" && $7 == "-" { print $4, $7 > "temp/station_sorted.csv"}
                    NR > 1 && (custom_id == "" || $1 == custom_id) && $4 != "-" && $5 == "-" && $8 != "-" { print $4, $8 > "temp/consumer_sorted.csv"}
                    '
                    ;;
            esac
                ;;
    esac

    awk -F ';' -v custom_id="$powerPlantID" "$filter" "$filePath">/dev/null

    stationNumber=$(wc -l < temp/station_sorted.csv)

    local endTime=$(date +%s%N)
    local timeMsg="$filePath sorted"
    displayTime "$timeMsg" "$startTime" "$endTime"
}


# Function to make graphs using output files
makeGraphs () {

    if [[ -f "output/lv_all.csv" ]]; then
        if ! command -v gnuplot &>/dev/null; then
            echo "Gnuplot is not installed. Use 'sudo apt install gnuplot' to install it."
            exit 3
        else 
            echo "Gnuplot is installed."
            # Script pour créer des graphiques (voir branche Guirec)
        fi
    fi
}


# Functions calls
runProgram () {
    # Suppr au cas où il y a eu une erreur avant pour test
    rm -f codeC/program_c
    
    verifyParameters "$@"

    processFolders

    startTime=$(date +%s%N)

    sortingData "$@"

    echo "Station number: $stationNumber"


    compilation "$2" "$3" "$4" "$stationNumber"

    # Faciliter les test
    rm -f codeC/program_c

    # cleanFolders

    makeGraphs

    local endTime=$(date +%s%N)
    local timeMsg="Program completed successfully"
    displayTime "$timeMsg" "$startTime" "$endTime"

    exit 0
}


runProgram "$@"