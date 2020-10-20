#!/bin/sh
mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
make
cd ..
./cmake-build-debug/assignment3 5 > output5.txt
./cmake-build-debug/assignment3 10 > output10.txt
./cmake-build-debug/assignment3 15 > output15.txt
