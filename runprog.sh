#!/bin/bash

#enter path to program here
programpath='./x64/Debug/Zadanie1.exe'
respath='./../Zad1Res/'

usage() {
    echo "Usage: $scriptname -l|--learningRate LEARNING-RATE -e|--epochs EPOCHS -m|--momentum MOMENTUM -b|--bias BIAS(true, false) -c|--count COUNT -C|--config COFIGURATION -h|--hidden OUTPUT_HIDDEN_LAYER(true, false) -op|--outputPath PATH -f|--filename TRAINING_SET_PATH"
}

CONFIG="4 2 4"
hidden="false"
filename="transformation.txt"
outputPath=""
count=1

# Parse args
scriptname=$(basename "$0")
for arg in "$@"; do
    if [[ "$arg" == '--help' ]]; then
        usage
        exit 0
    fi
done

count="1"

while (("$#")); do
    case "$1" in
        -l|--learningRate)
            learningRate=$2
            shift 2
            ;;
        -e|--epochs)
            epochs=$2
            shift 2
            ;;
        -m|--momentum)
            momentum=$2
            shift 2
            ;;
        -b|--bias)
            bias=$2
            shift 2
            ;;
        -c|--count)
            count=$2
            shift 2
            ;;
        -C|--config)
            CONFIG=$2
            shift 2
            ;;
        -h|--hidden)
            hidden=$2
            shift 2
            ;;
        -op|--outputPath)
            outputPath="$2"
            shift 2
            ;;
        -f|--filename)
            filename=$2
            shift 2
            ;;
        --) #end parsing
            shift
            break
            ;;
        -*|--*=) # unsupported flags
            echo "Error: Unsupported flag $1" >&2
            exit 1
            ;;
        *) # preserve positional arguments
            PARAM="$PARAMS $1"
            
            # CONFIG+="$1"
            shift
            # if [[ "$#" > 0 ]]; then
            #     CONFIG+=" "
            # fi
            ;;
    esac
done

# set positional arguments in their proper place
eval set -- "$PARAMS"

echo $PARAMS

if [[ $outputPath != "" ]] ; then
    mkdir "$respath""$outputPath" -p
    outputPath="$outputPath""/"  
fi


for c in $( eval echo {1..$count} )
do
    for i in {1.."$count"};
    do
        "$programpath" "$learningRate" "$momentum" "$epochs" "$bias" "$outputPath""$c""output_learningRate_""$learningRate""_momentum_""$momentum""_bias_""$bias""_config_""$CONFIG"".txt" $hidden "$filename" $CONFIG 
    done
done