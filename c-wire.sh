# Script shell pour trier les données


#!/bin/bash


# Fonction pour afficher un message d'erreur et le manuel
afficherErreur() {

    echo "ERREUR : $1" >&2
    cat manuel.txt
    exit 1
}


# Fonction de vérification des arguments
verifArguments() {

    # Vérifie la présence de l'argument de "-h" dans l'entrée ; $@ représente tous les arguments passés en entrée
    for arg in "$@"; do
        if [ "$arg" = "-h" ]; then
            cat manuel.txt
            exit 1
        fi
    done

    # Vérifier le nombre d'arguments
    if [ $# -gt 5 ] || [ $# -lt 1 ]; then
        afficherErreur "Vous devez entrer entre 1 et 5 arguments."
    fi

    # Vérifier que le premier argument est un lien symbolique valide
    if [ ! -e "$1" ] || [ ! -f "$1" ]; then
        afficherErreur "Le premier argument doit indiquer le chemin d'un fichier valide."
    fi

    # Vérification du deuxième argument
    case "$2" in
        hva|hvb|lv)
            ;;
        *)
            afficherErreur "Le deuxième argument doit être 'hva', 'hvb', ou 'lv'."
            ;;
    esac

    # Vérification du troisième argument
    case "$3" in
        comp|indiv|all)
            # Empêcher des combinaisons invalides
            if [[ "$2" == "hvb" && "$3" == "all" ]] || [[ "$2" == "hvb" && "$3" == "indiv" ]] || [[ "$2" == "hva" && "$3" == "all" ]] || [[ "$2" == "hva" && "$3" == "indiv" ]]; then
                afficherErreur "Les combinaisons 'hvb all', 'hvb indiv', 'hva all', et 'hva indiv' sont interdites."
            fi
            ;;
        *)
            afficherErreur "Le troisième argument doit être 'comp', 'indiv', ou 'all'."
            ;;
    esac

    # Vérification du cinquième argument (identifiant de centrale valide)
    if [ -n "$5" ]; then
        if [ ! -s "$5" ] || ! grep -q "^$5;" "$1"; then
            afficherErreur "Le quatrième argument doit être un identifiant de centrale valide."
        fi
    fi
}


# Fonction pour vérifier la présence des dossiers temp et graphs
verifDossier() {

    if  [ ! -e "temp" ] || [ ! -d "temp" ]; then
        mkdir temp

        # Si dossier temp non-vide, on le nettoie
        elif [ "$(ls -A temp)" ]; then
        rm -rf temp/*
    fi

    if [ ! -e "graphs" ] || [ ! -d "graphs" ]; then
        mkdir graphs
    fi

    if [ ! -e "input" ] || [ ! -d "input" ] || [ ! -e "input/DATA_CWIRE.csv" ] || [ ! -f "input/DATA_CWIRE.csv" ]; then
        echo "Le dossier input est absent ou mal configuré."
        echo "Le fichier d'entrée doit être nomé 'DATA_CWIRE.csv'"
        exit 1
    fi
}


# Fonction pour compiler les fichiers en C
compilation () {

    if [ ! -e "codeC/main.c" ]; then

    echo "ERREUR : le fichier main.c est manquant."

    else
        echo "Msg de test : fichier main.c bien présent."
        # make
    fi

    # Vérifie que la compilation s'est bien passée ; $? est la dernière commande exécutée (donc le make ici) alors si son code de sortie est différent de 0, il y a une erreur
    if [ $? -ne 0 ]; then
        echo "ERREUR : erreur de compilation !"
        exit 1
    fi
}

#Tri et transmission des données au programme C
triDonnées () {

    case "$2" in
        hva)
            #tail pour commencer à écrire à la deuxième ligne ; cut pour ne récup. que les colonnes 3 (hva) et 5 (comp); grep pour ne pas afficher les "-"
            tail -n +2 input/DATA_CWIRE.csv | cut -d';' -f3 | grep -v '^-*$' > temp/hva_id_temporaire.txt
            tail -n +2 input/DATA_CWIRE.csv | cut -d';' -f5 | grep -v '^-*$' > temp/comp_load_temporaire.txt
            # [...]
            ;;
        hvb)
            ;;

        lv)

            ;;
        *)
            echo "ERREUR : option non valide."
            ;;
    esac





}


#Nettoyer les dossiers après utilisation
nettoyage () {

    # rm -rf temp/*
    echo ""
    echo "Nettoyage"
}

if verifArguments "$1" "$2" "$3" "$4" "$5"; then

    verifDossier

    triDonnées "$1" "$2" "$3" "$4" "$5"

    nettoyage


    echo "Shrek"


fi
