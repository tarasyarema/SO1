#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Error: Wrong number of arguments."
    exit 1
fi

var=$1
len=${#var}
inv=""

for (( i = 0; i < $len; ++i ))
do
    inv=$inv${var:$(($len-$i-1)):1}
done

if [ $inv == $var ]
then
    echo "És un palíndorm."
else
    echo "No és un palíndorm."
fi

exit 0
