#!/bin/bash


# Shell script to run and sort data


# Displays the program help manual
display_help() {
    echo "CWIRE: this program processes data for an electricity distribution."
    echo ""
    echo "Usage:"
    echo "      $0 <path_file.csv> <station_type> <consumer_type> [power_plant_id]"
    echo "      Note : you must place your input file in '/input' directory and name it 'DATA_CWIRE.csv'."
    echo ""
    echo "Example:"
    echo "      $0 input/DATA_CWIRE.csv lv comp 3"
    echo ""
    echo "Arguments:"
    echo "      <path_file.csv>  Specifies the location of the input .csv file (mandatory)."
    echo "      <station_type>   Type of station to process: hva, hvb or lv (mandatory)."
    echo "      <consumer_type>  Type of consumer to process: all, comp or indiv (mandatory)."
    echo "      [power_plant_id]     Filters the results for a specific power plant (optional)."
    echo ""
    echo "      -h               Displays program help manual (optional)."
    echo ""
    echo "WARNING: The following options are forbidden:"
    echo "      * hvb all"
    echo "      * hvb indiv"
    echo "      * hva all"
    echo "      * hva indiv"
    echo ""
    exit 0
}


# Displays reduced program help
display_mini_help() {
    echo "Usage: $0 <path_file.csv> <station_type> <consumer_type> [power_plant_id]"
    echo "Use the -h parameter to get full help."
    exit 1
}


# Parameters verification
verifyParameters() {
    # Verify is "-h" is present
    # OU utiliser getops mais je ne comprends pas comment ça fonctionnev :(
    for option in "$@"; do
        case $option in
            -h) 
                display_help
            ;;
        esac
    done

    # Verify number of parameters
    if [ $# -gt 5 ] || [ $# -lt 1 ]; then
        echo "You must enter between 1 and 5 arguments"
        display_mini_help
    fi

    if [ ! -f "$1" ]; then
        echo "The first argument must indicate the path to a valid file."
        display_mini_help
    fi

    # Check second parameter
    case "$2" in
        hva|hvb|lv)
            ;;
        *)
            echo "Second argument must be 'hva', 'hvb', or 'lv'."
            display_mini_help
            ;;
    esac

    # Check third parameter
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

    # Check fourth parameter (valid plant identifier)
    if [ -n "$4" ]; then
        if ! grep -q "^$4;" "$1"; then
            echo "The fourth argument must be a valid power plant identifier."
            display_mini_help
        fi
    fi
}


# Check the presence of temp and graph folders
verifyFolders() {
        rm -rf temp/*

        mkdir -p graphs input temp output

    if [ ! -f "input/DATA_CWIRE.csv" ]; then
        echo "You must place your input file in /input directory and name it 'DATA_CWIRE.csv'."
        display_mini_help
        exit 1
    fi
}


# Start C program compilation
compilation () {
    if [ ! -f "codeC/main.c" ]; then
        echo "ERROR: main.c is missing."
        exit 1
    elif [ -f codeC/program_c ]; then
        echo "ERROR: program_c already exists."
        exit 1
    else
        make --no-print-directory -C codeC TYPE=$1 CONSUMER=$2
    fi

    # Checks that compilation has gone well
    if [ $? -ne 0 ]; then
        echo "ERROR : compilation error."
        exit 2
    fi
}


# Sorting function
sortingData () {

    # We use the awk function to sort data. Usage : awk 'pattern { action }' file.
    # We send the sorted data through a pipe (standard input) for fast data transmission.
    # Options : -F to indicate separating character, -v to indicate a variable. “custom_id” variable allows information to be sorted for a single plant only.

    case "$2" in
        hvb)
            awk -F ';' -v custom_id="$4" 'NR > 2 && (custom_id == "" || $1 == custom_id) && $2 != "-" && $3 == "-" { print $2, $7, $8 }' "$1" | ./codeC/program_c "hvb" "comp"
            ;;

        hva)
            awk -F ';' -v custom_id="$4" 'NR > 2 && (custom_id == "" || $1 == custom_id) && $3 != "-" && $2 == "-" { print $3, $7, $8 }' "$1" | ./codeC/program_c "hva" "comp"
            ;;

        lv)
            case "$3" in
                all)
                    awk -F ';' -v custom_id="$4" 'NR > 2 && (custom_id == "" || $1 == custom_id) && $4 != "-" { print $4, $7, $8 }' "$1" | ./codeC/program_c "lv" "all"
                    ;;

                comp)
                    awk -F ';' -v custom_id="$4" 'NR > 2 && (custom_id == "" || $1 == custom_id) && $4 != "-" && $6 == "-" { print $4, $7, $8 }' "$1" | ./codeC/program_c "lv" "comp"
                    ;;

                indiv)
                    awk -F ';' -v custom_id="$4" 'NR > 2 && (custom_id == "" || $1 == custom_id) && $4 != "-" && $5 == "-" { print $4, $7, $8 }' "$1" | ./codeC/program_c "lv" "indiv"
                    ;;
            esac
                ;;
    esac
}


# Displays elapsed time for execution of a command
#displayTime() {
#    TIMEFORMAT=%R
#    TIME_ELAPSED=time sortingData "$@"
#    echo ""
#    echo "Tri et transmission des données réussi en ${TIME_ELAPSED}."
#}


# Clean folders after execution
clean () {
    rm -rf temp/*
    rm codeC/program_c
}


#makeGraphs () {
#if ! command -v gnuplot 2>&1 /dev/null; then
#   echo "Gnuplot is not installed. To install it, use 'sudo apt insall gnuplot'."
#   exit 3
#fi
#}


verifyParameters "$@"

verifyFolders

compilation "$2" "$3"

sortingData "$@"

clean

#makeGraphs

exit 0