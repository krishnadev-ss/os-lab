#! /bin/bash

echo "enter the string :"
read str

#word=$(echo "$str" | wc -w)
#echo $word
#reverse=`echo $str | rev`
#echo $reverse

count=0
i=0
while [ $i -lt ${#str} ]
do
if [ "${str:$i:1}" == " " ]
then
count=$((count+1))
fi
((i++))
done
count=$((count+1))
echo the number of strings in the words are $count

