#!/bin/bash


# Shell script to sort 


show_help() {
    echo "================================="
    echo "C-WIRE"
    echo "================================="
    echo "This script processes data for an electricity distribution."
    echo
    echo "Required arguments:"
    echo "1. Path to the data file (mandatory)"
    echo "   - Specifies the location of the input .csv file."
    echo "2. Type of station to process (mandatory)"
    echo "   - Possible values:"
    echo "     * hvb (high-voltage B)"
    echo "     * hva (high-voltage A)"
    echo "     * lv (low-voltage)"
    echo "3. Type of consumer to process (mandatory)"
    echo "   - Possible values:"
    echo "     * comp (businesses)"
    echo "     * indiv (individuals)"
    echo "     * all (all)"
    echo "   - WARNING:"
    echo "     The following options are prohibited:"
    echo "     * hvb all"
    echo "     * hvb indiv"
    echo "     * hva all"
    echo "     * hva indiv"
    echo
    echo "4. Power plant identifier (optional)"
    echo "   - Filters the results for a specific power plant."
    echo "5. Help option (-h) (optional and priority)"
    echo "   - If present, all other options are ignored."
    echo "   - Displays this detailed help information."
    echo
    echo "Usage examples:"
    echo "./c-wire.sh input/DATA_CWIRE.csv hva comp"
    echo "./c-wire.sh input/DATA_CWIRE.csv all -h"
    echo "================================="
    exit 0
}


show_mini_help() {
    echo "Input error."
    echo "Usage: $0 [options] <file_path> <station_type> <consumer_type> [plant_id]"
    echo "Use the -h parameter to get full help."
    exit 1
}


# Parameters verification
verifyParameters() {

    # Verify is "-h" is present
    while getopts ":h" option; do
        case $option in
            h) 
                show_mini_help
            ;;
        esac
    done

    # Verify number of parameters
    if [ $# -gt 5 ] || [ $# -lt 1 ]; then
        echo "You must enter between 1 and 5 arguments"
        show_mini_help
    fi

    if [ ! -f "$1" ]; then
        echo "The first argument must indicate the path to a valid file."
        show_mini_help
    fi

    # Check second parameter
    case "$2" in
        hva|hvb|lv)
            ;;
        *)
            echo "Second argument must be 'hva', 'hvb', or 'lv'."
            ;;
    esac

    # Check third parameter
    case "$3" in
        comp|indiv|all)
            # Preventing invalid combinations
            if [[ "$2" == "hvb" && "$3" == "all" ]] || [[ "$2" == "hvb" && "$3" == "indiv" ]] || [[ "$2" == "hva" && "$3" == "all" ]] || [[ "$2" == "hva" && "$3" == "indiv" ]]; then
                echo "Les combinaisons 'hvb all', 'hvb indiv', 'hva all', et 'hva indiv' sont interdites."
            fi
            ;;
        *)
            echo "The third argument must be 'comp', 'indiv', or 'all'."
            show_mini_help
            ;;
    esac

    # Check fifth parameter (valid plant identifier)
    if [ -n "$5" ]; then
        if [ ! -s "$5" ] || ! grep -q "^$5;" "$1"; then
            echo "The fourth argument must be a valid plant identifier."
        fi
    fi
}


# Function to check the presence of temp and graph folders
verifyFolders() {

        rm -rf temp/*

        mkdir -p graphs input temp

    if [ ! -f "input/DATA_CWIRE.csv" ] ; then
        echo "The input file must be named 'DATA_CWIRE.csv'"
        exit 1
    fi
}


# Function to start C program compilation
compilation () {

    if [ ! -f "codeC/main.c" ]; then
    echo "ERREUR : le fichier main.c est manquant."

    else
        # make
    fi

    # Checks that compilation has gone well
    if [ $? -ne 0 ]; then
        echo "ERREUR : erreur de compilation."
        exit 1
    fi
}

# Sorting function
sortingData () {

    # Utilisation de la commande "time programme" elle est très précise mais sort trop d'infos qu'il est possible de filtrer


    case "$2" in
        hva)

            ;;
        hvb)
            ;;

        lv)

            ;;
        *)
            echo "ERREUR : invalid input."
            ;;
    esac



}


# Clean folders after execution
clean () {

    # rm -rf temp/*

}

# AWK
# awk -F ";" '$1 == "1" && $2 == "1"' fichier.csv

verifyParameters $@;

    verifyFolders

    sortingData $@

    clean


    echo "Shrek"

