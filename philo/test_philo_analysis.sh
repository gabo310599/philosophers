#!/bin/bash

PHILO=./philo

GREEN="\033[32m"
RED="\033[31m"
YELLOW="\033[33m"
RESET="\033[0m"

echo -e "${YELLOW}===================================="
echo "      PHILO ANALYSIS TESTER"
echo -e "====================================${RESET}"

#######################################
echo -e "\n${YELLOW}Running simulation for analysis...${RESET}"

timeout 8s $PHILO 5 800 200 200 > sim.txt

#######################################
echo -e "\n${YELLOW}Analyzing meal distribution${RESET}"

for i in 1 2 3 4 5
do
    COUNT=$(grep "$i is eating" sim.txt | wc -l)
    echo "Philosopher $i ate $COUNT times"
done

#######################################
echo -e "\n${YELLOW}Checking fairness${RESET}"

MIN=$(grep "is eating" sim.txt | awk '{print $2}' | sort | uniq -c | awk '{print $1}' | sort -n | head -n1)
MAX=$(grep "is eating" sim.txt | awk '{print $2}' | sort | uniq -c | awk '{print $1}' | sort -n | tail -n1)

echo "Min meals: $MIN"
echo "Max meals: $MAX"

DIFF=$((MAX-MIN))

if [ "$DIFF" -gt 5 ]; then
    echo -e "${RED}WARNING: Possible starvation (meal imbalance)${RESET}"
else
    echo -e "${GREEN}Fair meal distribution${RESET}"
fi

#######################################
echo -e "\n${YELLOW}Checking prints after death${RESET}"

LINE=$(grep -n "died" sim.txt | cut -d: -f1)

if [ -n "$LINE" ]; then
    TOTAL=$(wc -l < sim.txt)

    if [ "$LINE" -lt "$TOTAL" ]; then
        echo -e "${RED}ERROR: prints detected after death${RESET}"
    else
        echo -e "${GREEN}No prints after death${RESET}"
    fi
else
    echo -e "${YELLOW}No death occurred in this run${RESET}"
fi

#######################################
echo -e "\n${YELLOW}Checking time precision${RESET}"

grep "died" sim.txt

#######################################
echo -e "\n${YELLOW}CPU usage test${RESET}"

START=$(date +%s)

timeout 6s $PHILO 200 800 200 200 > /dev/null

END=$(date +%s)

ELAPSED=$((END-START))

echo "Execution time: $ELAPSED seconds"

#######################################
echo -e "\n${YELLOW}Deadlock detection${RESET}"

timeout 5s $PHILO 4 410 200 200 > deadlock.txt

if grep -q "is eating" deadlock.txt; then
    echo -e "${GREEN}No deadlock detected${RESET}"
else
    echo -e "${RED}Possible deadlock${RESET}"
fi

#######################################
echo -e "\n${YELLOW}Analysis complete${RESET}"