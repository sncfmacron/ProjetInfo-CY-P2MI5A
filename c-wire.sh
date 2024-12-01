#!/bin/bash

# Fonction pour afficher un message d'erreur et le manuel
afficherErreur() {

    echo "ERREUR : $1" >&2
    cat manual.txt
    exit 1
}

# Fonction de vérification des arguments
verifArguments() {

    # Vérifie la présence de l'argument de "-h" dans l'entrée ; $@ représente tous les arguments passés en entrée
    for arg in "$@"; do
        if [ "$arg" = "-h" ]; then
            cat manual.txt
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
        comb|indiv|all)
            # Empêcher des combinaisons invalides
            if [[ "$2" == "hvb" && "$3" == "all" ]] || [[ "$2" == "hvb" && "$3" == "indiv" ]] || [[ "$2" == "hva" && "$3" == "all" ]] || [[ "$2" == "hva" && "$3" == "indiv" ]]; then
                afficherErreur "Les combinaisons 'hvb all', 'hvb indiv', 'hva all', et 'hva indiv' sont interdites."
            fi
            ;;
        *)
            afficherErreur "Le troisième argument doit être 'comb', 'indiv', ou 'all'."
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

    if  [ ! -e "tmp" ] || [ ! -d "tmp" ]; then
        mkdir tmp

        # Si dossier tmp non-vide, on le nettoie
        elif [ "$(ls -A tmp)" ]; then
        rm -rf tmp
    fi

    if [ ! -e "graphs" ] || [ ! -d "graphs" ]; then
        mkdir graphs
    fi

}

# Fonction pour compiler les fichiers en C
compilation () {

    if [ ! -e "codeC/main.c" ]; then

    echo "ERREUR : le fichier main.c est manquant"

    else
        echo "Msg de test : fichier main.c bien présent"
        # make
    fi

    # Vérifie que la compilation s'est bien passée ; $? est la dernière commande exécutée (donc le make ici) alors si son code de sortie est différent de 0, il y a une erreur
    if [ $? -ne 0 ]; then
        echo "ERREUR : erreur de compilation !"
        exit 1
    fi

}

if verifArguments "$1" "$2" "$3" "$4" "$5"; then

    verifDossier

    echo "Shrek"




fi