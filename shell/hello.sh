#! /bin/bash
echo "enter string1:"
read str1
echo "enter string2:"
read str2

if [ $str1 = $str2 ] 
then 
echo "strings are equal"
else
echo "strings are not equal"
fi
concat=`echo $str1$str2`
echo $concat
echo $str1**$str2

echo ${str1:0:10} #get substring from o th index to 10 length
echo ${str1#*name} #delete name