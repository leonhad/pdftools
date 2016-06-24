#!/bin/bash

rm -rf out/
build-wrapper --out-dir out make clean all
cppcheck -v --enable=all --xml -j 4 -I src src 2> out/cppcheck.xml
rats -w 3 --xml src/ > out/rats.xml
sonar-runner

