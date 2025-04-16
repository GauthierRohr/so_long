#!/bin/bash

# Couleurs pour une meilleure lisibilité
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

EXE_DIR="./"
EXECUTABLE="${EXE_DIR}so_long"
MAPS_DIR="maps/"

if [ ! -f "$EXECUTABLE" ]; then
    echo -e "${RED}Erreur: L'exécutable $EXECUTABLE n'existe pas.${NC}"
    echo "Exécute 'make' pour compiler le programme."
    exit 1
fi

test_map() {
    local map=$1
    local expected_to_pass=$2
    local map_path="${MAPS_DIR}${map}"
    
    echo -e "${BLUE}=== Test de la map: $map ===${NC}"
    
    if [ ! -f "$map_path" ]; then
        echo -e "${RED}Erreur: La map $map_path n'existe pas.${NC}"
        return
    fi
    
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
        --log-file=/tmp/valgrind_log.txt "$EXECUTABLE" "$map_path" >/dev/null 2>&1
    exit_code=$?
    
    # Analyse complète des fuites
    leaks=$(grep -A10 "LEAK SUMMARY" /tmp/valgrind_log.txt | grep -E "definitely lost: [^0]|indirectly lost: [^0]|possibly lost: [^0]|still reachable: [^0]")
    errors=$(grep "ERROR SUMMARY" /tmp/valgrind_log.txt | grep -v "0 errors")

    if [ -z "$leaks" ] && [ -z "$errors" ]; then
        if [ $exit_code -eq 0 ] && [ $expected_to_pass -eq 1 ]; then
            echo -e "${GREEN}✓ OK - Map valide, aucune fuite mémoire${NC}"
        elif [ $exit_code -ne 0 ] && [ $expected_to_pass -eq 0 ]; then
            echo -e "${GREEN}✓ OK - Map invalide rejetée, aucune fuite mémoire${NC}"
        elif [ $exit_code -eq 0 ] && [ $expected_to_pass -eq 0 ]; then
            echo -e "${RED}✗ ÉCHEC - Map invalide acceptée${NC}"
        else
            echo -e "${RED}✗ ÉCHEC - Map valide rejetée${NC}"
        fi
    else
        echo -e "${RED}✗ FUITES DÉTECTÉES (y compris still reachable) :${NC}"
        grep -A10 "LEAK SUMMARY" /tmp/valgrind_log.txt
        grep "ERROR SUMMARY" /tmp/valgrind_log.txt
    fi
    echo
}

test_arg_error() {
    local args="$@"
    local desc="$args"
    
    if [ -z "$args" ]; then
        desc="pas d'arguments"
    fi
    
    echo -e "${BLUE}=== Test avec $desc ===${NC}"
    
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
        --log-file=/tmp/valgrind_log.txt "$EXECUTABLE" $args >/dev/null 2>&1
    
    leaks=$(grep -A10 "LEAK SUMMARY" /tmp/valgrind_log.txt | grep -E "definitely lost: [^0]|indirectly lost: [^0]|possibly lost: [^0]|still reachable: [^0]")
    errors=$(grep "ERROR SUMMARY" /tmp/valgrind_log.txt | grep -v "0 errors")

    if [ -z "$leaks" ] && [ -z "$errors" ]; then
        echo -e "${GREEN}✓ OK - Pas de fuites mémoire${NC}"
    else
        echo -e "${RED}✗ FUITES DÉTECTÉES (y compris still reachable):${NC}"
        grep -A10 "LEAK SUMMARY" /tmp/valgrind_log.txt
        grep "ERROR SUMMARY" /tmp/valgrind_log.txt
    fi
    echo
}

echo -e "${YELLOW}==================================${NC}"
echo -e "${YELLOW}=== TEST DE FUITES POUR SO_LONG ===${NC}"
echo -e "${YELLOW}==================================${NC}"
echo

# Parcours automatique des maps
for map in $(ls "$MAPS_DIR" | grep -E '\.ber$'); do
    if [[ "$map" == 0* ]]; then
        test_map "$map" 1
    else
        test_map "$map" 0
    fi
done

# Tests d'erreurs d'arguments
echo -e "${YELLOW}=== Erreurs d'arguments ===${NC}"
test_arg_error
test_arg_error "maps/0_medium.ber" "maps/0_little.ber"
test_arg_error "fichier_inexistant.ber"
test_arg_error "maps"
test_arg_error "maps/0_medium"
test_arg_error "./so_long"

# Cas avec noms bizarres
echo -e "${YELLOW}=== Caractères spéciaux ===${NC}"
test_arg_error "maps/\"bad_name\".ber"
test_arg_error "maps/'; rm -rf /; echo '.ber"

echo -e "${YELLOW}=== Fin des tests ===${NC}"
echo -e "${BLUE}Vérification complète! Si tous les tests sont passés sans fuites, félicitations!${NC}"
