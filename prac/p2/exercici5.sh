#!/bin/env bash

usage="Usage: bash $0 {NIUB} {problemes|practiques} {nou_grup}"

if [ $# -ne 3 ]
then
    echo "Error: Wrong number of arguments."
    echo "$usage"
    exit 1
fi

if [ $2 != "problemes" -a $2 != "practiques" ]
then
    echo "Error: Wrong second parameter {$2}."
    echo "$usage"
    exit 1
fi

file="alumnes.csv"

awk -F ";" -v niub=$1 -v class=$2 -v group=$3 -v file=$file '{
    if ( $1 == niub && class == "practiques" ) 
        print $1";"group";"$3 > file;
    else if ( $1 == niub && class == "problemes" )
        print $1";"$2";"group > file;
    else
        print $1";"$2";"$3 > file;
    }' $file

echo "Grup de $2 modificat."

exit 0