#!/bin/sh
seed=1
./rr $seed >> output.txt
./hpq_pe $seed >> output.txt
