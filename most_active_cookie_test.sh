#!/bin/bash

if which dos2unix ; then
	DOSUNIX="dos2unix"
elif which fromdos ; then
	DOSUNIX="fromdos"
else
	DOSUNIX="cat"
fi

echo "===================="
PASSED=0
CHECKED=0

rm -f most_active_cookie
rm -f generate_testcases

g++ most_active_cookie.cpp -o most_active_cookie
g++ generate_testcases.cpp -o generate_testcases

DatesArray=("2022-05-21" "2022-05-20" "2022-05-19" "2022-05-18" "2022-05-17")

for i in Program_tests/ManualTest/Testcases/*; do
    for dateIndex in "${!DatesArray[@]}"; do
        CHECKED=$(( ${CHECKED} + 1 ))
        ./most_active_cookie $i -d ${DatesArray[$dateIndex]} > tempFile
        sort -o tempFile tempFile
        program=$(<tempFile)
        rm -f tempFile
        base=$(basename ${i} .csv)
        answer_file=Program_tests/ManualTest/Answers/${base}_answer_${DatesArray[$dateIndex]}.txt
        answer=$(<${answer_file})

        if [ "${program}" == "${answer}" ]; 
        then
            echo "PASSED. ManualTest ${base} ${DatesArray[$dateIndex]}"
            PASSED=$(( ${PASSED} + 1 ))
        else
            echo "FAILED. ${base} ${DatesArray[$dateIndex]}"
            echo "program: "
            echo "${program}"
            echo ""
            echo "answer: "
            echo "${answer}"
            echo ""
        fi
    done
done

TestcasesCount=(100 1000 10000 100000 1000000)
cookiesCount=8

mkdir -p Program_tests/AutomatedTest/Testcases
mkdir -p Program_tests/AutomatedTest/Answers

rm -f Program_tests/AutomatedTest/Testcases/*
rm -f Program_tests/AutomatedTest/Answers/*

for count in "${TestcasesCount[@]}"; do
    ./generate_testcases ${cookiesCount} ${count} automated_log_${count}
    for dateIndex in "${!DatesArray[@]}"; do
        ./most_active_cookie Program_tests/AutomatedTest/Testcases/automated_log_${count}.csv -d ${DatesArray[$dateIndex]} > tempFile
        sort -o tempFile tempFile
        program=$(<tempFile)
        rm -f tempFile
        answer_file=Program_tests/AutomatedTest/Answers/automated_log_${count}_answer-${DatesArray[$dateIndex]}.txt
        sort -o ${answer_file} ${answer_file}
        answer=$(<${answer_file})
        CHECKED=$(( ${CHECKED} + 1 ))
        if [ "${program}" == "${answer}" ]; 
        then
            echo "PASSED. automated_log_${count} ${DatesArray[$dateIndex]}"
            PASSED=$(( ${PASSED} + 1 ))
        else
            echo "FAILED. automated_log_${count} ${DatesArray[$dateIndex]}"
            echo "program: "
            echo "${program}"
            echo ""
            echo "answer: "
            echo "${answer}"
            echo ""
        fi
    done

    rm -f ${answerPath}

done

echo "####################"
echo "Passed ${PASSED} out of ${CHECKED}"
echo ""
    