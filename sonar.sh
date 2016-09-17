#!/bin/bash

rm -rf out/
build-wrapper --out-dir out/ make clean all
make check
xsltproc cppunit-1.x-to-junit-1.0.xsl src/cppunit.xml > out/cppunit.xml
rm src/cppunit.xml
gcovr -x -r src > out/gcov.xml
cppcheck -v --enable=all --xml -I src src test 2> out/cppcheck.xml
rats -w 3 --xml . > out/rats.xml
find . | grep ".*\.cpp\|.*\.h" | vera++ -d -s -c out/vera.xml
sonar-scanner
