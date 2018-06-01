#!/bin/bash

#echo "input:"
#read line
#i=0
#while [ "$i" -lt "$line" ]
#do
#	echo "hello world"
#	let "i += 1"
#	i = `expr $i + 1`
#done

#echo "please password:"
#read line

i=0
while [ "$i" -le 3 ]
do
	echo "please password:"
	read line
	if [ "$line" -eq "123" ]
	then 
		echo "success"
		break;
	else
		echo "failed!"
		let "i += 1"
done
exit(0)

