#!/bin/env bash

usage="Usage: bash $0 {user}"

if [ $# -ne 1 ]
then
    echo "Error: Wrong number of arguments."
    echo "$usage"
    exit 1
fi

ps aux | grep "$1" | awk '{sum += $5} END {print "VSZ: "sum" bytes"}'
ps aux | grep "$1" | awk '{sum += $6} END {print "RSS: "sum" bytes"}'

exit 0