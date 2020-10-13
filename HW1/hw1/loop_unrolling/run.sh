#! /bin/bash

printf "Running non-unrolled loop code:\n"
./loop 3 268435456

printf "\nRunning unrolled loop code:\n"
./unroll 3 268435456
