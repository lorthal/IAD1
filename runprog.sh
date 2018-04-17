#!/bin/bash

#enter path to program here
programpath='echo program'

usage() {
    echo "Usage: $scriptname -l|--learningRate LEARNING-RATE -e|--epochs EPOCHS -m|--momentum MOMENTUM -b|--bias BIAS COFIGURATION"
}

# runprog()
# {
#     for filename in *; do
#         if [[ -f "$filename" && "$filename" =~ $init_filename_regex ]]; then
#             filename_root="${filename%.txt}_${1}_${2,,}"
#             sol_filename="${filename_root}_sol.txt"
#             stats_filename="${filename_root}_stats.txt"
#             $programpath "$1" "$2" "$filename" "$sol_filename" "$stats_filename"
#         fi
#     done
# }

CONFIG=""

# Parse args
scriptname=$(basename "$0")
for arg in "$@"; do
    if [[ "$arg" == '--help' ]]; then
        usage
        exit 0
    fi
done

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
            
            CONFIG+="$1"
            shift
            if [[ "$#" > 0 ]]; then
                CONFIG+=" "
            fi
            ;;
    esac
done

# set positional arguments in their proper place
eval set -- "$PARAMS"

echo $PARAMS

for i in $( eval echo {0..$count} )
do
    $programpath "$learningRate" "$momentum" "$epochs" "$bias" "$CONFIG"
done