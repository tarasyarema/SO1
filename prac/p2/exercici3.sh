#!/bin/env bash

usage="Usage: bash $0 {directory}"

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

echo "$(find $1 -type f | wc -l) files"
# Utilitzo la comanda `xargs` per a poder passar-li a la comanda `ls -l`
# cada linia retornada per la comanda `find` anterior
echo "$(find $1 -type f | xargs ls -l | awk '{sum += $5} END {print sum}') bytes"

exit 0
