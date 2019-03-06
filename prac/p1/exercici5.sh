#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Error: Wrong number of arguments."
    exit 1
fi

if [ ! -d $1 ]
then
    echo "Error: First argument should be a directory."
    exit 1
fi

dump=$(ls $1)

for entry in $dump
do
    echo "$1$entry"
    
    if [ -d "$1$entry" ]
    then
        bash exercici5.sh "$1$entry/"
    fi

done

exit 0
