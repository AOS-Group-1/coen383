#!/bin/sh
seed=1
mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
make
cd ..
./cmake-build-debug/assignment2 $seed >> output.txt
./cmake-build-debug/assignment2_rr $seed >> output.txt
./cmake-build-debug/assignment2_hpf $seed >> output.txt
