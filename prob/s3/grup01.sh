#!/bin/bash

usage="$ bash grup01.sh directory/"

if [ $# -ne 1 ]
then
    echo "Error: Wrong number of arguments."
    echo "$usage"
    exit 1
fi

if [ ! -d $1 ]
then
    echo "Error: The first argument should be a directory."
    echo "$usage"
    exit 1
fi

dirs=$(find $1 -type d)

for dir in $dirs
do
    nfiles=$(find $dir -maxdepth 1 -type f | wc -l) 
    echo "directori: $dir nfiles: $nfiles"
done

exit 0
