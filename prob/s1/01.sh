#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Wrong number of arguments."
    echo "   Usage: $ bash me.sh file"
    exit 1
fi

if [ -d $1 ]
then
    echo "You passed a directory as argument."
    echo "   Usage: $ bash me.sh file"
    exit 1
fi

exist=$(cat $1 | wc -l)
no_exist=$(cat $1 | xargs ls -l &> /dev/stdout | grep "cannot" | wc -l)

echo "Existeixen: $(($exist - $no_exist))"
echo "No existeixen: $no_exist"
