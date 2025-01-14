#!/usr/bin/bash

function buildTheSourceCode() {
    local filename="$1"
    local arg="$2"
    local name="${filename%.*}"
    local extension="${filename##*.}"
    if [ "$extension" == "c|cpp" ]; then
        [ "$extension" == "c" ] && gcc -I../../include $filename $arg
        [ "$extension" == "cpp" ] && g++ -I../../include $filename $arg
    fi
}

olPWD=$(pwd)
cd "$(dirname "$0")" || { sleep 0.5; exit 1; }
buildTheSourceCode "$1" "$2"
cd "$olPWD"