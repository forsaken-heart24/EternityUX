#!/bin/bash

# no, roundma will hate me :[
wrapperApplicationSourceCode="$1"

compile_program() {
    local theDawnGivenValue="$1"
    local theDawnArguments="$2"
    
    # return false / as failed if the argument is not available.
    [ -z "$theDawnGivenValue" ] && return 1;

    # let's cherry-pick the compile and run it, otherwise we should return false / as failed to alert the user.
    if [ "$(echo $theDawnGivenValue | cut -c $(( $(echo $theDawnGivenValue | wc -c) - 3 ))-$(echo $theDawnGivenValue | wc -c) )" == "c" ]; then
        gcc ${theDawnArguments}
    elif [ "$(echo $theDawnGivenValue | cut -c $(( $(echo $theDawnGivenValue | wc -c) - 3 ))-$(echo $theDawnGivenValue | wc -c) )" == "cpp" ]; then
        g++ ${theDawnArguments}
    else
        return 1
    fi
}

if [ -z "$1" ] || [ -f "${wrapperApplicationSourceCode}" ]; then
    wrapperApplicationSourceCodeIntoTheExecutable=$(echo "${wrapperApplicationSourceCode}" | cut -c 1-$(( $(echo $wrapperApplicationSourceCode | wc -c ) - 5)))
    echo " - Building ${wrapperApplicationSourceCodeIntoTheExecutable} app..."
    compile_program "${wrapperApplicationSourceCode}" "-I../include ${wrapperApplicationSourceCode} -o ${wrapperApplicationSourceCodeIntoTheExecutable} -mwindows" || {
        echo " - The build is failed, please try again later!"
        return 1
    }
    echo Hit "Enter" to try testing the build!
    read awwwhelllnahbro
    chmod 755 ${wrapperApplicationSourceCodeIntoTheExecutable}
    ./${wrapperApplicationSourceCodeIntoTheExecutable} --test
fi