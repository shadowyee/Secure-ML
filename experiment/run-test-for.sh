#!/bin/bash
cd ../build
make
cd bin
filepath=../../experiment/matrix-generate-test-result.txt
# matrix_size=(32 64 128 256 512 1024 2048 4096)
n=(1000 1000 1000 10000 10000 10000 100000 100000 100000)
d=(100 500 1000 100 500 1000 100 500 1000)
t=(8 8 8 80 80 80 100 100 100)
b=125
for i in {0..8}
do
    echo "Starting test at $(date)" | tee -a $filepath
    echo "========================" | tee -a $filepath
    echo "n=${n[$i]}, d=${d[$i]}, t=${t[$i]}, |B|=${b}" | tee -a $filepath
    echo "========================" | tee -a $filepath
    ./matrix_generate 1 8000 ${n[i]} ${d[i]} ${t[i]} ${b} & ./matrix_generate 2 8000 ${n[i]} ${d[i]} ${t[i]} ${b}| tee -a $filepath
    # kill -KILL $!
    echo "==========end============" | tee -a $filepath
done
