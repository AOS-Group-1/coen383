#!/bin/sh
seed=1
./mkdir p2
./cd p2
./cmake ..
./make
./p2/assignment2 $seed >> output.txt
./p2/assignment2_rr $seed >> output.txt
./p2/assignment2_hpf $seed >> output.txt
