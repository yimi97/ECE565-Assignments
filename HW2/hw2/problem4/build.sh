#! /bin/bash

gcc -O3 -o matrix_multiplication matrix_multiplication.c -lrt
gcc -O3 -o matrix_multiplication_tiling matrix_multiplication_tiling.c -lrt