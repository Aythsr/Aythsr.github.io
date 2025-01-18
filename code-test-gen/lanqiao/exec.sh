#! /bin/bash

g++ std.cpp -o std.out

for((i=1;i<=10;++i))
do

    ./std.out < ./data/in$i.txt > ./data/out$i.txt
    if [ $? -eq 0 ]
    then
        echo ${i} ok!
    else
        echo '-------------' ${i} No!
    fi
done