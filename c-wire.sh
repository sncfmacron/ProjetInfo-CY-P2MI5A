#!/bin/bash

# Fonction pour afficher un message d'erreur et le manuel stocké dans /src
afficherErreur() {
    echo "ERREUR : $1" >&2
    cat src/manual.txt
    exit 1
}

# Fonction de vérification des arguments
verifArguments() {
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

# Vérifie la présence de l'argument de "-h" dans l'entrée ; $@ représente tous les arguments passés en entrée
for arg in "$@"; do
    if [ "$arg" = "-h" ]; then
        cat src/manual.txt
        exit 0
    fi
done

if verifArguments "$1" "$2" "$3" "$4" "$5"; then

    echo "Shrek"

fi