#!/bin/bash

p="/mnt/d/Semestr 6/IAD/Zad1"

"$p""/runprog.sh" -l 0.1 -m 0 -b false -e 5000 -C "4 1 4"
"$p""/runprog.sh" -l 0.1 -m 0 -b false -e 5000 -C "4 2 4"
"$p""/runprog.sh" -l 0.1 -m 0 -b false -e 5000 -C "4 3 4"

"$p""/runprog.sh" -l 0.1 -m 0 -b true -e 5000 -C "4 1 4"
"$p""/runprog.sh" -l 0.1 -m 0 -b true -e 5000 -C "4 2 4"
"$p""/runprog.sh" -l 0.1 -m 0 -b true -e 5000 -C "4 3 4"