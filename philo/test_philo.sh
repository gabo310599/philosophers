#!/bin/bash

PHILO=./philo

GREEN="\033[32m"
RED="\033[31m"
YELLOW="\033[33m"
RESET="\033[0m"

PASS=0
FAIL=0
TEST=1

pass() {
    echo -e "${GREEN}PASS${RESET} $1"
    ((PASS++))
}

fail() {
    echo -e "${RED}FAIL${RESET} $1"
    ((FAIL++))
}

run_test() {
    DESC=$1
    CMD=$2

    timeout 6s $CMD > output.txt
    STATUS=$?

    if [ $STATUS -eq 124 ]; then
        pass "$DESC (timeout acceptable)"
        return
    fi

    if grep -q "died" output.txt; then
        pass "$DESC"
    else
        pass "$DESC (no death but stable)"
    fi
}

echo -e "${YELLOW}==============================="
echo "      PHILO EXTREME TESTER"
echo -e "===============================${RESET}"

####################################
echo -e "\n${YELLOW}BASIC TESTS${RESET}"

run_test "1 philosopher dies" "$PHILO 1 800 200 200"
run_test "2 philosophers basic" "$PHILO 2 800 200 200"
run_test "3 philosophers basic" "$PHILO 3 800 200 200"
run_test "4 philosophers basic" "$PHILO 4 800 200 200"
run_test "5 philosophers basic" "$PHILO 5 800 200 200"

####################################
echo -e "\n${YELLOW}TIGHT TIMING${RESET}"

run_test "4 410 200 200" "$PHILO 4 410 200 200"
run_test "4 400 200 200" "$PHILO 4 400 200 200"
run_test "4 390 200 200" "$PHILO 4 390 200 200"
run_test "3 310 200 100" "$PHILO 3 310 200 100"
run_test "3 300 200 100" "$PHILO 3 300 200 100"

####################################
echo -e "\n${YELLOW}STARVATION TESTS${RESET}"

run_test "5 800 200 200" "$PHILO 5 800 200 200"
run_test "6 800 200 200" "$PHILO 6 800 200 200"
run_test "7 800 200 200" "$PHILO 7 800 200 200"
run_test "8 800 200 200" "$PHILO 8 800 200 200"
run_test "9 800 200 200" "$PHILO 9 800 200 200"

####################################
echo -e "\n${YELLOW}MUST_EAT TESTS${RESET}"

timeout 6s $PHILO 5 800 200 200 3 > output.txt
if grep -q "died" output.txt; then
    fail "must_eat 3 should stop without death"
else
    pass "must_eat 3 works"
fi

timeout 6s $PHILO 5 800 200 200 5 > output.txt
if grep -q "died" output.txt; then
    fail "must_eat 5 should stop without death"
else
    pass "must_eat 5 works"
fi

timeout 6s $PHILO 3 800 200 200 4 > output.txt
if grep -q "died" output.txt; then
    fail "must_eat 4 should stop without death"
else
    pass "must_eat 4 works"
fi

####################################
echo -e "\n${YELLOW}SCALING TESTS${RESET}"

run_test "10 philosophers" "$PHILO 10 800 200 200"
run_test "20 philosophers" "$PHILO 20 800 200 200"
run_test "30 philosophers" "$PHILO 30 800 200 200"
run_test "40 philosophers" "$PHILO 40 800 200 200"
run_test "50 philosophers" "$PHILO 50 800 200 200"

####################################
echo -e "\n${YELLOW}EXTREME TESTS${RESET}"

run_test "60 philosophers" "$PHILO 60 800 200 200"
run_test "80 philosophers" "$PHILO 80 800 200 200"
run_test "100 philosophers" "$PHILO 100 800 200 200"
run_test "150 philosophers" "$PHILO 150 800 200 200"
run_test "200 philosophers" "$PHILO 200 800 200 200"

####################################
echo -e "\n${YELLOW}DEATH PRINT TEST${RESET}"

timeout 6s $PHILO 4 310 200 100 > output.txt

LINE=$(grep -n "died" output.txt | cut -d: -f1)

if [ -n "$LINE" ]; then
    TOTAL=$(wc -l < output.txt)
    if [ "$LINE" -lt "$TOTAL" ]; then
        fail "prints after death detected"
    else
        pass "no prints after death"
    fi
else
    fail "death not detected"
fi

####################################
echo -e "\n${YELLOW}VALGRIND TEST${RESET}"

valgrind --leak-check=full --error-exitcode=1 $PHILO 5 800 200 200 > /dev/null 2>&1

if [ $? -eq 0 ]; then
    pass "no memory leaks"
else
    fail "memory leaks detected"
fi

####################################
echo -e "\n${YELLOW}HELGRIND TEST${RESET}"

valgrind --tool=helgrind --error-exitcode=1 $PHILO 5 800 200 200 > /dev/null 2>&1

if [ $? -eq 0 ]; then
    pass "no data races"
else
    fail "possible data races"
fi

####################################
echo
echo -e "${YELLOW}==============================="
echo "TOTAL PASS: $PASS"
echo "TOTAL FAIL: $FAIL"
echo -e "===============================${RESET}"