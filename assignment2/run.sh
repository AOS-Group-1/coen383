#!/bin/sh
seed=1
rm ../p2/output.txt
cd ..
mkdir p2
cd p2
cmake ..
make
../p2/assignment2 $seed >> output.txt
../p2/assignment2_rr $seed >> output.txt
../p2/assignment2_hpf $seed >> output.txt
