#! /bin/bash
source base.sh

g++ ${stdp} -o ${stde}

rm ${dir}*.ans

for i in $(ls ${dir}*in)
do
    j=${i%.in}.ans
    ./${stde} < $i > $j
    if [ $? -eq 0 ]
    then
        echo ${i} ok!
    else
        echo '-------------' ${i} rm!
        rm $i $j
    fi
done

