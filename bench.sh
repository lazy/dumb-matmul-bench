#!/bin/sh

# We have 28 cores per numa node
# Also we won't use core 0, because well, linux
export MKL_NUM_THREADS=20
n=16384
# n=32768

# Make sure to install MKL using your system distro package manager first
echo === Building
make

echo === C++
taskset -c 1-20 numactl --cpunodebind=0 --membind=0 ./matrix_mult $n

# Make sure to init anaconda environment first
echo === Python
taskset -c 1-20 numactl --cpunodebind=0 --membind=0 python3 ./matrix_mult.py $n
