#! /bin/bash

g++ data.cpp -o data.out

for ((i=1;i<=10;++i))
do

    ./data.out  > ./data/in$i.txt

done