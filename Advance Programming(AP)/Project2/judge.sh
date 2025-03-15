#!/bin/bash

C_RED="\033[31m"
C_GRN="\033[32m"
C_YLW="\033[33m"
C_BLU="\033[34m"
C_CYN="\033[36m"
C_ULN="\033[4m"
C_CLR="\033[0m"

DIR_TESTS="$(pwd)/tests"

SINGLE_FILE_NAME="src/main.cpp"
EXE="main.out"
EXE_OUTPUT="out.txt"
COMPILER="g++ -std=c++20"

TIME_LIMIT=2s
DIFF_TOOL="sdiff -sWB"
VERBOSE_DIFF_TOOL="sdiff -Wsw 108"

TABLES_CSV="src/tables.csv"
STUDENTS_CSV="src/students.csv"

function cxx_compile {
    echo -e "${C_CYN}${C_ULN}Compiling $SINGLE_FILE_NAME...${C_CLR}"
    if [[ ! -e "$SINGLE_FILE_NAME" ]]; then
        echo -e "${C_RED}File $SINGLE_FILE_NAME does not exist${C_CLR}" >&2
        return 1
    fi
    if ! $COMPILER "$SINGLE_FILE_NAME" -o $EXE >/dev/null 2>&1; then
        echo -e "${C_RED}Compile Error${C_CLR}" >&2
        return 1
    fi
    echo -e "${C_GRN}Compiled Successfully${C_CLR}"
}

function run_tests {
    local passed=0
    local failed=0

    if [[ ! -f "$EXE" ]]; then
        echo -e "${C_RED}Executable not found${C_CLR}" >&2
        return 1
    fi

    echo -e "${C_BLU}Running tests...${C_CLR}"

    for testcase in "$DIR_TESTS"/*; do
        [[ -d "$testcase" ]] || continue

        local number=$(basename "$testcase")
        local input="$testcase/$number.in"
        local solution="$testcase/$number.out"

        echo -e "${C_YLW}Running test: $number${C_CLR}"

        if ! timeout $TIME_LIMIT ./$EXE "$TABLES_CSV" "$STUDENTS_CSV" < "$input" >"$EXE_OUTPUT" 2>&1; then
            echo -e "${C_RED}Timed out${C_CLR}"
            ((failed++))
            continue
        fi

        if $DIFF_TOOL "$EXE_OUTPUT" "$solution" >/dev/null; then
            echo -e "${C_GRN}Accepted${C_CLR}"
            ((passed++))
        else
            echo -e "${C_RED}Wrong answer${C_CLR}"
            ((failed++))
            $VERBOSE_DIFF_TOOL "$EXE_OUTPUT" "$solution"
        fi
    done

    echo
    echo -e "        Passed: ${C_GRN}$passed${C_CLR} out of $((passed + failed))"
    echo -e "        Failed: ${C_RED}$failed${C_CLR} out of $((passed + failed))"
    echo
}

function test_code() {
    cxx_compile && run_tests
}

while [[ $# -gt 0 ]]; do
    case $1 in
    -t | --test)
        test_code
        exit 0
        ;;
    *)
        echo "Unknown option: $1" >&2
        exit 1
        ;;
    esac
done
