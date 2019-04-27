#!/bin/env bash

usage="Usage: bash $0 {directory} {extension}"

if [ $# -ne 2 ]
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

dir=$1

# Fix final slash (if missing)
if [ ${dir:${#dir}-1:1} != "/" ]
then
    dir=$dir"/"
fi

find $dir -type f -name "*.$2" -print

exit 0
