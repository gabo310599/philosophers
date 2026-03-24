#!/bin/sh

PHILO=./philo

PASS=0
FAIL=0

pass() {
echo "PASS $1"
PASS=$((PASS + 1))
}

fail() {
echo "FAIL $1"
FAIL=$((FAIL + 1))
}

run_test() {
DESC="$1"
CMD="$2"
SHOULD_DIE="$3"

timeout 5 $CMD > output.txt 2>&1
STATUS=$?

if [ $STATUS -eq 124 ]; then
    fail "$DESC timeout"
    return
fi

DEATHS=$(grep -c died output.txt)

if [ "$SHOULD_DIE" = "yes" ]; then
    if [ "$DEATHS" -eq 0 ]; then
        fail "$DESC no death"
        return
    fi
    if [ "$DEATHS" -gt 1 ]; then
        fail "$DESC multiple deaths"
        return
    fi
else
    if [ "$DEATHS" -gt 0 ]; then
        fail "$DESC unexpected death"
        return
    fi
fi

if [ "$DEATHS" -eq 1 ]; then
    LINE=$(grep -n died output.txt | cut -d: -f1)
    TOTAL=$(wc -l < output.txt)

    if [ "$LINE" -lt "$TOTAL" ]; then
        fail "$DESC prints after death"
        return
    fi
fi

pass "$DESC"

}

echo "START TESTS"

run_test "1 philo" "$PHILO 1 800 200 200" yes
run_test "2 philos" "$PHILO 2 800 200 200" no
run_test "5 philos" "$PHILO 5 800 200 200" no

run_test "tight" "$PHILO 4 400 200 200" yes
run_test "very tight" "$PHILO 4 100 100 100" yes

timeout 5 $PHILO 5 800 200 200 3 > output.txt 2>&1
if [ $? -eq 124 ]; then
fail "must eat timeout"
elif grep -q died output.txt; then
fail "must eat death"
else
pass "must eat ok"
fi

run_test "20 philos" "$PHILO 20 800 200 200" no
run_test "50 philos" "$PHILO 50 800 200 200" no
run_test "100 philos" "$PHILO 100 800 200 200" no

echo "RESULT"
echo "PASS: $PASS"
echo "FAIL: $FAIL"
