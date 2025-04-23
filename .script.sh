#!/bin/bash

MANGENTA="\033[35m"
BOLD="\033[1m"
CLEAR_LINE="\033[2K"
LINE_UP="\033[1A"
RED="\033[31m"
WHITE="\033[37m"
GRAY="\033[90m"
BLUE="\033[34m"
GREEN="\033[32m"
RESET="\033[0m"

spin[0]=$GREEN"⠁"
spin[1]=$GREEN"⠃"
spin[2]=$GREEN"⠇"
spin[3]=$GREEN"⠧"
spin[4]=$GREEN"⠷"
spin[5]=$GREEN"⠿"
spin[6]=$GREEN"⠷"
spin[7]=$GREEN"⠧"
spin[8]=$GREEN"⠇"
spin[9]=$GREEN"⠃"

echo -ne "$WHITE${spin[0]}$RESET Loading...\n"
for i in {1..3}; do
    for j in "${spin[@]}"; do
        echo -ne "$LINE_UP$WHITE$j$RESET Processing...\n"
        sleep 0.1
    done
done

printf "$LINE_UP$CLEAR_LINE$GREEN$BOLD✔ Compilation finished successfully!$WHITE$BOLD$RESET\n"

