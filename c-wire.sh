#!/bin/bash


# Shell script to run and sort data


# Displays the program help manual
display_help() {
    echo "This script processes data for an electricity distribution."
    echo ""
    echo "- Parameters description:"
    echo ""
    echo "   <path_file.csv>  Specifies the location of the input .csv file (required)."
    echo "   <station_type>   Type of station to process: hva, hvb or lv (required)."
    echo "   <consumer_type>  Type of consumer to process: all, comp or indiv (required)."
    echo "   [central_id]     Filters the results for a specific central (optional)."
    echo "   -h               Displays program help manual (optional)."
    echo ""
    echo "- WARNING: The following options are forbidden:"
    echo "    * hvb all"
    echo "    * hvb indiv"
    echo "    * hva all"
    echo "    * hva indiv"
    echo ""
    echo "Usage:"
    echo ""
    echo "$0 <path_file.csv> <station_type> <consumer_type> [central_id]"
    echo ""
    echo "Usage example:"
    echo ""
    echo "$0 input/DATA_CWIRE.csv hvb comp 3"
    echo ""
    exit 0
}


# Displays reduced program help
display_mini_help() {
    echo "Input error."
    echo "Usage: $0 <path_file.csv> <station_type> <consumer_type> [central_id]"
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

    # Check fifth parameter (valid plant identifier)
    if [ -n "$5" ]; then
        if [ ! -s "$5" ] || ! grep -q "^$5;" "$1"; then
            echo "The fourth argument must be a valid plant identifier."
            exit 1
        fi
    fi
}


# Check the presence of temp and graph folders
verifyFolders() {
        rm -rf temp/*

        mkdir -p graphs input temp

    if [ ! -f "input/DATA_CWIRE.csv" ]; then
        echo "The input file must be named 'DATA_CWIRE.csv'"
        exit 1
    fi
}


# Start C program compilation
compilation () {
    if [ ! -f "codeC/main.c" ]; then
        echo "ERROR: main.c is missing."
        exit 1
    elif [ -f program_c ]; then # plutôt "codeC/program_c" mais je le coderai après
        echo "ERROR: program_c already exists."
        exit 1
    else
        make --no-print-directory -C codeC run TYPE=$1 CONSUMER=$2
    fi

    # Checks that compilation has gone well
    if [ $? -ne 0 ]; then
        echo "ERROR : compilation error."
        exit 1
    fi
}


# Displays time
displayTime () {
    # configurer time ici pour pas faire une formule de 1000km dans sortingData()
    echo ""
    # time
}


# Sorting function
sortingData () {
    # awk 'pattern { action }' fichier ; exemple : awk -F ";" '$1 == "1" && $2 == "1"' fichier.csv*

    case "$2" in
        hvb)
            awk -F ';' 'NR > 2 && $2 != "-" && $7 != "-" && $3 == "-"{ print $1, $2, $7 }' "$1" > temp/stations_sorted.csv
            # awk -F ';' 'NR > 2 && $2 != "-" { print $1, $2, $5, $7, $8 }' "$1" > temp/load_sorted.csv
            compilation "hvb"
            ;;

        hva)

            awk -F ';' 'NR > 2 && $2 != "-" && $7 != "-" && $3 == "-"{ print $1, $2, $7 }' "$1" > temp/stations_sorted.csv
            # awk -F ';' 'NR > 2 && $3 != "-" { print $1, $3, $5, $7, $8 }' "$1" > temp/load_sorted.csv
            compilation "hva"
            ;;

        lv)
            case "$3" in
                all)
                    awk -F ';' 'NR > 2 && $4 != "-" && $7 != "-" { print $1, $4, $7 }' "$1" > temp/stations_sorted.csv
                    compilation "lv" "all"

                    ;;

                comp)
                    
                    ;;

                indiv)

                    ;;
            esac
                ;;
    esac
}


# Clean folders after execution
clean () {
    # rm -rf temp/*
    # rm codeC/progam_c
    echo ""
}


verifyParameters $@

verifyFolders

sortingData $@

clean

exit 0