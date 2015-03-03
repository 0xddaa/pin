#!/bin/sh

if [ -z $1 ]; then
    echo "Usage: ./run <program>"
    exit
fi

make clean
make
sudo pin -t obj-ia32/codecoverage.so -o "log/$1_"`date +"%T_%m-%d"` -- $1
