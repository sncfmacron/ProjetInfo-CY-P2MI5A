#!/bin/bash


# Shell script to run and sort data


# Displays the program help manual
display_help() {
    echo "This script processes data for an electricity distribution."
    echo ""
    echo "Usage: $0 <path_file.csv> <station_type> <consumer_type> [central_id]"
    echo ""
    echo "Parameters description:"
    echo ""
    echo "   <path_file.csv>  Specifies the location of the input .csv file (required)."
    echo "   <station_type>   Type of station to process: hva, hvb or lv (required)."
    echo "   <consumer_type>  Type of consumer to process: all, comp or indiv (required)."
    echo "   [central_id]     Filters the results for a specific central (optional)."
    echo "   -h               Displays c-wire help manual (optional)."
    echo ""
    echo "- WARNING: The following options are forbidden:"
    echo "    * hvb all"
    echo "    * hvb indiv"
    echo "    * hva all"
    echo "    * hva indiv"
    echo ""
    echo "Usage examples:"
    echo "$0 input/DATA_CWIRE.csv hva comp"
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
    while getopts ":h" option; do
        case $option in
            h) 
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
            ;;
    esac

    # Check third parameter
    case "$3" in
        comp|indiv|all)
            # Preventing invalid combinations
            if [[ "$2" == "hvb" && "$3" == "all" ]] || [[ "$2" == "hvb" && "$3" == "indiv" ]] || [[ "$2" == "hva" && "$3" == "all" ]] || [[ "$2" == "hva" && "$3" == "indiv" ]]; then
                echo "The following combinations are forbidden: 'hvb all', 'hvb indiv', 'hva all', and 'hva indiv'."
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
        fi
    fi
}


# Check the presence of temp and graph folders
verifyFolders() {

        rm -rf temp/*

        mkdir -p graphs input temp

    if [ ! -f "input/DATA_CWIRE.csv" ] ; then
        echo "The input file must be named 'DATA_CWIRE.csv'"
        exit 1
    fi
}


# Start C program compilation
compilation () {

    if [ ! -f "codeC/main.c" ]; then
        echo "ERROR : main.c is missing."
        exit 1
    elif [ -f program_c ]; then
        echo "ERROR: program_c already exists."
        exit 1
    else
        gcc codeC/main.c -o program_c
        # make
    fi

    # Checks that compilation has gone well
    if [ $? -ne 0 ]; then
        echo "ERROR : compilation error."
        exit 1
    fi
}

# Sorting function
sortingData () {

    # awk -F ";" '$1 == "1" && $2 == "1"' fichier.csv*
    # awk 'pattern { action }' fichier
    # Utilisation de la commande "time programme" elle est très précise mais sort trop d'infos qu'il est possible de filtrer

    case "$2" in
        hvb)
            awk -F ';' 'NR > 2 && $2 != "-" { print $1, $2, $5, $7, $8 }' "$1" | ./program_c
            ;;
        hva)
            time(awk -F ';' 'NR > 2 && $3 != "-" { print $1, $3, $5, $7, $8 }' "$1" | ./program_c) 2>&1
            echo "Tri réussi"
            ;;
        lv)
            case "$3" in
                all)
                    awk -F ';' 'NR > 2 { print $1, $4, $5, $6, $7, $8 }' "$1" | ./program_c
                    ;;

                comp)
                    awk -F ';' 'NR > 2 && $5 != "-" { print $1, $4, $5, $7, $8 }' "$1" | ./program_c
                    ;;

                indiv)
                    awk -F ';' 'NR > 2 && $6 != "-" { print $1, $4, $6, $7, $8 }' "$1" | ./program_c
                    ;;
            esac
                ;;
    esac


}


# Clean folders after execution
clean () {

    rm -rf temp/*
    rm program_c

}


verifyParameters $@;

    verifyFolders

    compilation

    sortingData $@ && clean







exit 0