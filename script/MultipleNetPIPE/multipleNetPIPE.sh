#!/bin/bash          
CS="sudo xl create -c netpipe-llamaNET-"
if [ -z "$1" ]
then
	echo "Number of processes must be defined"
	echo "Usage: bash llamaMultiple.sh <#processes> <offset>"
	exit
fi

if [ -z "$2" ]
then
	echo "Offset must be defined"
	echo "Usage: bash llamaMultiple.sh <#processes> <offset>"
	exit
else
	OFFSET=$2
fi

echo "Launching $1 processes"
for ((i=0; i < $1; i++))
do
	CS2="${CS}$((i+OFFSET))"
	CS2="${CS2}.config &"
	eval $CS2
done
