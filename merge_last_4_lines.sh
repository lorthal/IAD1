#!/bin/bash

for filename in *; do
    if [[ $filename == [0-9]* ]]; then
        # cat "$filename" >> "hiddenOutput.txt"
        tail -4 "$filename" >> "hiddenOutput.txt"
    fi
done