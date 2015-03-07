#!/bin/sh

if [ -z $1 ]; then
    echo "Usage: ./run <program>"
    exit
fi

make

if [ -z $2 ]; then
    binary=`basename $1`
    date=`date +%T-%m-%d`
    pin -t obj-ia32/codecoverage.so -o "log/"$binary"_"$date -- $1
else
    pin -t obj-ia32/codecoverage.so -o "log/"$2 -- $1
    cat "log/"$2 | python -m json.tool | less
fi
