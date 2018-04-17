#!/bin/bash

for filename in *; do
    if [[ $filename == [0-9]* ]]; then
        tail -1 "$filename" >> "epochs.txt"
    fi
done