#!/bin/bash
cd ../build
make
cd bin
filepath=../../experiment/matrix-generate-test-result.txt
matrix_size=(32 64 128 256 512 1024 2048 4096)
i=$1
echo "Starting test at $(date)" | tee -a $filepath
echo "========================" | tee -a $filepath
echo "n=${matrix_size[$i]}, d=${matrix_size[$i]}, t=${matrix_size[$i]}, |B|=${matrix_size[$i]}" | tee -a $filepath
echo "========================" | tee -a $filepath
./matrix_generate 1 8000 ${matrix_size[i]} ${matrix_size[i]} ${matrix_size[i]} ${matrix_size[i]} & ./matrix_generate 2 8000 ${matrix_size[i]} ${matrix_size[i]} ${matrix_size[i]} ${matrix_size[i]} | tee -a $filepath
# kill -KILL $!
echo "==========end============" | tee -a $filepath

