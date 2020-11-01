#!/bin/sh
mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
make
cd ..

./cmake-build-debug/assignment4 > output.txt
