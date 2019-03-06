#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Error: Wrong number of arguments."
    exit 1
fi

if [ ! -d $1 ]
then
    echo "Error: The argument should be a directory."
    exit 1
fi

files=0
dirs=0

for i in $(ls $1)
do
    tmp=$1$i
    if [ -f $tmp ]
    then
        files=$(($files+1))
    elif [ -d $tmp ]
    then
        dirs=$(($dirs+1))
    fi
done

echo "Fitxers: $files"
echo "Directoris: $dirs"

exit 0
