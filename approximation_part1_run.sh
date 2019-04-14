#!/bin/bash

p="./"

for i in {1..20};
do
    "$p""/runprog.sh" -l 0.1 -m 0.6 -b true -e 500 -C "1 "$i" 1" -f "approximation_train_1.txt" -op "Approximation/Training_Set_1"
    "$p""/runprog.sh" -l 0.1 -m 0.6 -b true -e 500 -C "1 "$i" 1" -f "approximation_train_2.txt" -op "Approximation/Training_Set_2"
done