#!/bin/env bash

usage="Usage: bash $0 {directory} {extension} {string}"

if [ $# -ne 3 ]
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

# Utilitzo el primer exercici per simplificar aquest mateix
# És equivalent a copiar el codi del primer abans d'aquest 
# for i passar l'ouput al for
for file in $(bash exercici1.sh $1 $2)
do
    echo $file
    echo "la cadena $3 aparaeix $(grep $3 $file | wc -l) vegades"
done

exit 0