#!/bin/bash

if [ $# -ne 2 ]
then
    echo "Wrong number of arguments."
    exit 1
fi

if [ ! -d $1 ]
then
    echo "First argument should be a directory."
    exit 1
fi

var=$2
len=${#var}
dump=$(ls $1)

for file in $dump
do
    total=0
    
    if [ -f $file ]
    then

        for word in $(cat $file)
        do
            tmp=${word:0:$len}
            
            if [ $tmp == $var ]
            then
                echo "$file: $word"
                total=$(($total+1))
            fi
        done
        
        echo "Total $file: $total"
    fi

done

exit 0
