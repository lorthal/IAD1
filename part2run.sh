#!/bin/bash

p="/mnt/d/Semestr 6/IAD/Zad1"
r="/mnt/d/Semestr 6/IAD/Zad1Res/"

"$p""/runprog.sh" -l 0.1 -m 0.1 -b true -e 0.2 -C "4 2 4" -op "$r" -c 100
"$p""/runprog.sh" -l 0.1 -m 0.6 -b true -e 0.2 -C "4 2 4" -op "$r" -c 100
"$p""/runprog.sh" -l 0.1 -m 0.9 -b true -e 0.2 -C "4 2 4" -op "$r" -c 100
"$p""/runprog.sh" -l 0.5 -m 0.1 -b true -e 0.2 -C "4 2 4" -op "$r" -c 100
"$p""/runprog.sh" -l 0.5 -m 0.6 -b true -e 0.2 -C "4 2 4" -op "$r" -c 100
"$p""/runprog.sh" -l 0.5 -m 0.9 -b true -e 0.2 -C "4 2 4" -op "$r" -c 100
"$p""/runprog.sh" -l 0.9 -m 0.1 -b true -e 0.2 -C "4 2 4" -op "$r" -c 100
"$p""/runprog.sh" -l 0.9 -m 0.6 -b true -e 0.2 -C "4 2 4" -op "$r" -c 100
"$p""/runprog.sh" -l 0.9 -m 0.9 -b true -e 0.2 -C "4 2 4" -op "$r" -c 100