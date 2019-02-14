#!/bin/bash

if [ $# -ne 2 ]
then 
    echo "Nombre incorrecte de parametres"
    exit 1
fi

A=$1
B=$2 

if [ $A -gt $B ]
 then
  echo "$A es major que $B"
 else
  echo "$A es menor que $B"
fi 

exit 0
