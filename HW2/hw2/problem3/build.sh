#! /bin/bash

gcc -O3 -o test_bandwidth test_bandwidth.c -lrt
gcc -O3 -o test_bandwidth_large test_bandwidth_large.c -lrt