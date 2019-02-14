#!/bin/bash

if [ $# -ne 1 ]
then
   echo "Nombre de parametres incorrecte"
   exit 1
fi

fitxer=$1
paraules=$(cat $fitxer)
for i in $paraules 
do
  echo $i
done

exit 0

