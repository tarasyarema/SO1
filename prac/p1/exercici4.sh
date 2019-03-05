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

# L'argument -S ordena per mida decreixent
# d'aquesta manera el for posterior és més eficient
dump=$(ls -S $1)
min=$2
boo=0

for entry in $dump
do
    if [ -f $1$entry ] && [ $boo -eq 0 ]
    then
        list=$(ls -lo $1$entry)
        count=0
        
        for word in $list
        do
            count=$(($count+1))

            if [ $count -eq 4 ]
            then
                if [ $word -ge $min ]
                then
                    echo -e "$entry:\t$word Bytes"
                else
                    boo=1
                fi
                break
            fi

        done
    fi
done

exit 0
