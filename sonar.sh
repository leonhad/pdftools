#!/bin/bash

rm -rf out/
build-wrapper --out-dir ../pdftools-sonar make clean all check -j
cppcheck -v --enable=all --xml -j 4 -I src src test 2> ../pdftools-sonar/cppcheck.xml
rats -w 3 --xml . > ../pdftools-sonar/rats.xml
find . | grep ".*\.cpp\|.*\.h" | vera++ -d -s -c ../pdftools-sonar/vera.xml
sonar-runner

