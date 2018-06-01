# !/bin/bash


fun()
{
	str="hello world!"
	echo "hello fun"
	echo "fun :\$#=$#"
	echo "fun :\$1=$1"
	echo "fun :\$2=$2"
	echo "fun :\$3=$3"
#unset str  / local str="hello world"
	return 3;
}

#fun 123 abc
#val=$?
#echo "val = $val"
#echo "str = $str"
mystr=hello
echo "main run"

#. ./jbbb.sh // 没有新的解释器，用当前的环境中 bash
#souce ./jbbb.sh

#环境变量
export mystr 
./test.sh 
#./test.sh $mystr

