#!/bin/bash


# Shell script to compile program_c and sort data


# Displays the program help manual
display_help() {
    echo "CWIRE: this program processes data for an electricity distribution."
    echo ""
    echo "Usage:"
    echo "      $0 <file_path.csv> <station_type> <consumer_type> [power_plant_id]"
    echo "      Note : you must place your '.csv' input file in './input' directory."
    echo ""
    echo "Arguments:"
    echo "      <file_path.csv>  Location of the input file (mandatory)."
    echo "      <station_type>   Type of station to process: hva, hvb or lv (mandatory)."
    echo "      <consumer_type>  Type of consumer to process: all, comp or indiv (mandatory)."
    echo "      [power_plant_id] Filters the results for a specific power plant (optional)."
    echo ""
    echo "      -h               Displays help manual (optional)."
    echo ""
    echo "WARNING ! The following combinations are invalid:"
    echo "      * hvb all"
    echo "      * hvb indiv"
    echo "      * hva all"
    echo "      * hva indiv"
    echo ""
    echo "Example:"
    echo "      $0 input/DATA_CWIRE.csv lv comp 3"
    echo ""
    exit 0
}


# Displays reduced program help
display_mini_help() {
    echo ""
    echo "Usage: $0 <path_file.csv> <station_type> <consumer_type> [power_plant_id]"
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
    if [ $# -gt 5 ] || [ $# -lt 1 ]; then
        echo "You must provide at least the path to your input file, the station type and the consumer type."
        display_mini_help
    fi

    # ---------- A REFAIRE ----------
    # Verifying first parameter
    if [[ ! "$1" == input/*.csv ]]; then
        echo "The first argument must indicate a path to a valid '.csv' file located in './input' directory."
        display_mini_help
    fi

    # Verifying second parameter
    case "$2" in
        hva|hvb|lv)
            ;;
        *)
            echo "Second argument must be 'hva', 'hvb', or 'lv'."
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
            echo "The third argument must be 'comp', 'indiv', or 'all'."
            display_mini_help
            ;;
    esac

    # Verifying fourth parameter (valid powerplant identifier)
    # 'grep' checks if the id exists in input file
    if [ -n "$4" ]; then
        if ! grep -q "^$4;" "$1"; then
            echo "The fourth argument must be a valid power plant identifier."
            display_mini_help
        fi
    fi
}


# Clean folders and unused file
cleanFolders () {
    rm -rf temp/*
}


# Starts program_c compilation using 'make'
compilation () {
    # If program_c doesn't exist we start the compilation

    # --- VERIFIER POUR DISQUE DUR ---

    if [ ! -f "codeC/program_c" ]; then
        # An argument is used to avoid 'make' sending messages when browsing files.
        # We give arguments to 'make' so program_c knows which type of station and consumer to process.
        make --no-print-directory -C codeC

        # Checks that compilation has gone well
        if [ $? -ne 0 ]; then
            echo "ERROR : compilation error."
            exit 2
        fi  
    fi
}


# Prepares directories for program execution
processFolders() {
    cleanFolders

    # These folders are created if they don't exist. If they exist, nothing happens
    mkdir -p graphs input temp output
}


# Sorting data function and transmission to program_c
sortingData () {

    # We use 'awk' to sort data through a pipe (standard input) and filters to send only relevant informations.
    # Arguments in 'awk' line : -F to indicate separating character, -v to indicate a variable.

    # 'date' command gives the elapsed seconds since 01/01/1970.

    startTime=$(date +%s.%N)


    filePath="$1"
    stationType="$2"
    consumerType="$3"
    powerPlantID="$4"

    case "$2" in
        hvb)
            filter='NR > 2 && (custom_id == "" || $1 == custom_id) && $2 != "-" && $3 == "-" { print $2, $7, $8 }'
            ;;
        hva)
            filter='NR > 2 && (custom_id == "" || $1 == custom_id) && $3 != "-" && $4 == "-" { print $3, $7, $8 }'
            ;;
        lv)
            case "$3" in
                all)
                    filter='NR > 2 && (custom_id == "" || $1 == custom_id) && $4 != "-" { print $4, $7, $8 }'
                    ;;
                comp)
                    filter='NR > 2 && (custom_id == "" || $1 == custom_id) && $4 != "-" && $6 == "-" { print $4, $7, $8 }'
                    ;;
                indiv)
                    filter='NR > 2 && (custom_id == "" || $1 == custom_id) && $4 != "-" && $5 == "-" { print $4, $7, $8 }'
                    ;;
            esac
                ;;
    esac

    awk -F ';' -v custom_id="$powerPlantID" "$filter" "$filePath" | ./codeC/program_c "$stationType" "$consumerType" "$powerPlantID"


    elapsedTime=$(printf "%.1f" $(echo "$(date +%s.%N) - $startTime" | bc))

    echo ""
    echo "--- The program was successfully completed in $elapsedTime seconds ---"
}


# Function to make graphs using output files
makeGraphs () {

    if [ -f "output/lv_all.csv" ]; then
        if ! command -v gnuplot &>/dev/null; then
            echo "Gnuplot is not installed. Use 'sudo apt install gnuplot' to install it."
            exit 3
        else 
            echo "Gnuplot installed."
            # Script pour créer des graphiques
        fi
    fi
}


verifyParameters "$@"

processFolders

compilation "$2" "$3"

sortingData "$@"

cleanFolders

makeGraphs

# Pour faire des tests plus facilement, on l'enlevera
rm codeC/program_c

exit 0