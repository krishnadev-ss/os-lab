#! /bin/bash

#read -p 'username: ' user_var  #to read on the same line
#read -sp 'password: ' pass_var
#echo
#echo "username : $user_var"
#echo "password : $pass_var"




echo "enter the string:"
read str

i=0
vcount=0
jcount=0

while [ $i -lt ${#str} ]
do
    if [ "${str:$i:1}" == "a" -o "${str:$i:1}" == "e" -o "${str:$i:1}" == "i" -o "${str:$i:1}" == "o" -o "${str:$i:1}" == "u" ]
    then 
        ((vcount++))
    else
        ((jcount++))
    fi
    ((i++))
done

echo "no of vowels are $vcount"
echo "no of consonants are $jcount"
