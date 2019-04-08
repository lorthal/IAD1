#!/bin/bash

p="/mnt/d/Semestr 6/IAD/Zad1"

for i in {1..20};
do
    "$p""/runprog.sh" -l 0.1 -m 0.6 -b true -e 5000 -C "1 $1 1" -f "approximation_train_1.txt"
    "$p""/runprog.sh" -l 0.1 -m 0.6 -b true -e 5000 -C "1 $1 1" -f "approximation_train_2.txt"
done