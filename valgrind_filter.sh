#!/bin/bash

# Chemin vers votre exécutable minishell
MINISHELL_PATH="./minishell"

# Fichier temporaire pour stocker la sortie de Valgrind
TEMP_OUTPUT="/tmp/valgrind_output.txt"

# Exécuter Valgrind et stocker la sortie
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
         --verbose --log-file=$TEMP_OUTPUT $MINISHELL_PATH

# Filtrer la sortie
cat $TEMP_OUTPUT | grep -v -e "readline" -e "add_history" -e "/bin/ls" | \
    grep -E "definitely lost|indirectly lost|possibly lost|still reachable"

# Supprimer le fichier temporaire
rm $TEMP_OUTPUT