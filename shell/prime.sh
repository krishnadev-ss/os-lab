#! /bin/bash

echo "enter the num:"
read num
for (( i=2;i <= $num/2 ; ++i ))
do
if [ $(($i % 2)) == 0 ]
then 
echo "print number is not prime"
else
echo "number is prime"
fi

done