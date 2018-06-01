#!/bin/bash

echo hello; echo "hello world!"
echo "input"
read line

for i in `ls`
do 
	echo "i = $ls"
done

if [ "$line" -ge "10" ] #&& [ "$line" -lt "20" ]
then 
	echo "10<$line< 20"
else
	echo "error"

#if [ "$line" -gt "90" ] && [ "$line" -lt "100" ]
#then 
#	echo "A"
#elif [ "$line" -gt "80" ] && [ "$line" -lt "90" ]
#if [ -d "$line" ]
#then 
#	echo "$line is  dirent"
#elif [ -f "$line" ]
#then 
#	echo "$line is file"
#else 
#	echo "not find $line"

#fi

#if [ "$line = 1024" ]
#then 
#echo "=="
#else
#echo "!="
#fi

#if test "$line = 1023"
#then 
#	echo "="
#fi

#echo "line = $line"
#echo 'line = $line'
#echo "PATH = $PATH"
#echo "pid = $$"
#echo "num = $!"
#echo "\$0 = $0"

#echo "\$1 = $1"
#echo "\$2 = $2"

exit(0)
