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
        CHECKED=$(( ${CHECKED} + 1 ));
        ./most_active_cookie $i -d ${DatesArray[$dateIndex]} > tempFile
        sort -o tempFile tempFile
        program=$(<tempFile)
        rm -f tempFile
        base=$(basename ${i} .csv)
        answer_file=Program_tests/ManualTest/Answers/${base}_answer_${DatesArray[$dateIndex]}.txt
        answer=$(<${answer_file})

        if [ "${program}" == "${answer}" ]; 
        then
            PASSED=$(( ${PASSED} + 1 ));
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

echo "####################"
echo "Passed ${PASSED} out of ${CHECKED}"
echo ""
    