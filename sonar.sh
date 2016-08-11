#!/bin/bash

rm -rf out/
build-wrapper --out-dir out/ make clean all
./test/testsuit
xsltproc cppunit-1.x-to-junit-1.0.xsl cppunit.xml > out/cppunit.xml
rm cppunit.xml
gcovr -x --object-directory=$(pwd) > out/gcov.xml
cppcheck -v --enable=all --xml -I src src test 2> out/cppcheck.xml
rats -w 3 --xml . > out/rats.xml
find . | grep ".*\.cpp\|.*\.h" | vera++ -d -s -c out/vera.xml
sonar-runner

