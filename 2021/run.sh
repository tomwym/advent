#!/bin/bash

if [ ${2} = "-a" ] || [ ${2} = "--A" ] ; then
declare -a vals=($( seq -f "%02g" 1 ${1} ))
else
vals=${1}
fi

for i in "${vals[@]}" 
do
    ./main ${i}
done
