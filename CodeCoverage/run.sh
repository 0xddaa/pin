#!/bin/sh

if [ -z $1 ]; then
    echo "Usage: ./run <program>"
    exit
fi

make

if [ -z $2 ]; then
    pin -t obj-ia32/codecoverage.so -o "log/$1_"`date +"%T_%m-%d"` -- $1
else
    pin -t obj-ia32/codecoverage.so -o "log/"$2 -- $1
    cat "log/"$2 | python -m json.tool | less
fi
