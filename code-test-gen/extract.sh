#! /bin/bash


# exe $1 $2 提取$1压缩到$2


# ls $1
DIR=$1


cp -rf $DIR ./tmp/XJDFTMP

DIR='./tmp/XJDFTMP'
tmpz='zip_'$1

std1='std.c'
std2='std.cpp'

if [ -e $tmpz ]
then
    rm -rf $tmpz
    echo 'rm ok'
fi

mkdir $tmpz

mkdir -p $tmpz/data/
mkdir -p $tmpz/std/

name=$(basename $DIR/conName*)
conName=${name[0]#conName}

for dir in $(ls $DIR)
do
    echo $DIR/$dir ------------
    zip -rj $tmpz/data/${dir}_data.zip $DIR/$dir/test/*

    if [ -e $DIR/$dir/$std1 ]
    then
        cp  $DIR/$dir/$std1 $tmpz/std/${dir}_std.c
    fi

    if [ -e $DIR/$dir/$std2 ]
    then
        cp  $DIR/$dir/$std2 $tmpz/std/${dir}_std.cpp
    fi
done

rm $DIR -rf

zxp=${tmpz}_${conName}.zip
rm $zxp
zip $zxp $tmpz -rvm

