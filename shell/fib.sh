#! /bin/bash

echo enter the number
read num
first=0
second=1

while [ $(($second+$first)) -le $num ]; do
    third=$(($first+$second))
    first=$second
    second=$third
    index=$(($first+1))
    while [ $index -lt $second ]; do
    echo $index
    index=$(($index+1))
    done
done

