#! /bin/bash
source ./base.sh

g++ $datap -o $datae

for ((i=1;i<=20;++i))
do
    ./$datae  > $dir$i.in
    echo $i ok!
done

for ((i=21;i<=40;++i))
do
    ./$datae  > $dir$i.in
    echo $i ok!
done

