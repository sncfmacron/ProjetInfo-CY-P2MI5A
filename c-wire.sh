#!/bin/bash


# Shell script to run programand sort data


# Displays the program help manual
display_help() {
    echo "CWIRE: this program processes data for an electricity distribution."
    echo ""
    echo "Usage:"
    echo "      $0 <path_file.csv> <station_type> <consumer_type> [power_plant_id]"
    echo "      Note : you must place your input file in '/input' directory and name it 'DATA_CWIRE.csv'."
    echo ""
    echo "Arguments:"
    echo "      <path_file.csv>  Location of the input .csv file (mandatory)."
    echo "      <station_type>   Type of station to process: hva, hvb or lv (mandatory)."
    echo "      <consumer_type>  Type of consumer to process: all, comp or indiv (mandatory)."
    echo "      [power_plant_id] Filters the results for a specific power plant (optional)."
    echo ""
    echo "      -h               Displays program help manual (optional)."
    echo ""
    echo "WARNING: the following combinations are invalid:"
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
        echo "You must provide at least the path to 'DATA_CWIRE.csv', the station type and the consumer type."
        display_mini_help
    fi

    if [ ! -f "$1" ]; then
        echo "The first argument must indicate the path to a valid file."
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
    # 'grep' checks if the id exists in 'DATA_CWIRE.csv'
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
    rm -f codeC/program_c # CMT: il me semble que c'est pas demander. A voir plus tard
}


# Checking the presence of temp and graph folders
verifyFolders() {
        cleanFolders

        mkdir -p graphs input temp output

    if [ ! -f "input/DATA_CWIRE.csv" ]; then #CMT: le fichier peut s'appeler autre chose que data_cwire. A supprimer 
        echo "You must place your input file in '/input' directory and name it 'DATA_CWIRE.csv'."   #CMT: ./input quand il y a /nom_repertoire au début d'un fichier ou d'un répertoire, ça définit un chemin absolue. Alors que ./nom_repertoire c'est relatif
        display_mini_help                                                                           #CMT: 
    fi
    
    if [ ! -f "codeC/main.c" ]; then #CMT:  A supprimer
        echo "ERROR: main.c is missing in '/codeC' directory."
        exit 1
    elif [ -f "codeC/program_c" ]; then #CMT a suppr
        echo "ERROR: program_c already exists in '/codeC' directory."
        exit 1
    fi
}


# Starts C program compilation using 'make'
compilation () {
    # An argument is used to avoid the 'make' program sending messages when browsing files.
    # We give arguments to 'make' so C program knows which type of station and consumer to process.
    make --no-print-directory -C codeC

    # Checks that compilation has gone well
    if [ $? -ne 0 ]; then
        echo "ERROR : compilation error."
        exit 2
    fi
}


# Sorting data function and transmission to C program
sortingData () {

    # We use 'awk' to sort data through a pipe (standard input) and filters to send only relevant information.
    # Arguments in 'awk' line : -F to indicate separating character, -v to indicate a variable.

    # 'date' command gives the elapsed seconds since 01/01/1970.

    START_TIME=$(date +%s)

    filePath="$1"
    stationType="$2"
    consumerType="$3"
    powerPlantID="$4"

    case "$2" in
        hvb)
            # Très lent pour le fichier de 9 millions de lignes
            # ~ 17 stations hva par secondes et pour le traitement hvb rien ne se passe
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

    awk -F ';' -v custom_id="$powerPlantID" "$filter" "$filePath" | ./codeC/program_c "$stationType" "$consumerType" "$powerPlantID" #CMT: le truc sur Discord

    END_TIME=$(date +%s)

    echo ""
    echo "--- The program was successfully completed in $((END_TIME - START_TIME)) seconds ---"
}


# Function to make graphs using output files
makeGraphs () {

    if [ -f "output/lv_all.csv" ]; then
        if [ ! command -v gnuplot &> /dev/null ]; then
            echo "Gnuplot is not installed. Use 'sudo apt install gnuplot' to install it."
            exit 3
        else 
            echo "Gnuplot installed."
            # Script pour créer des graphiques
        fi
    fi
}


verifyParameters "$@"

verifyFolders

compilation "$2" "$3"

sortingData "$@"

cleanFolders

makeGraphs

exit 0