#!/bin/bash

resF="results"
logDir="./logs"
resultsDir="./res"

if [[ ! -e ${logDir} ]]
then
    mkdir -p ${logDir}
fi

if [[ ! -e ${resultsDir} ]]
then
    mkdir -p ${resultsDir}
fi

echo "ts,qArr,instArr,startEx,endEx,flops" > "${resultsDir}/${resF}.csv"

for s in `seq 1 1000000 75000000`
do
    suffix="1_${s}"
    echo "ts,qArr,instArr,startEx,endEx,flops" > "${resultsDir}/${resF}_${s}.csv"
    echo "$(pwd)/dejavu_platform.xml"
    echo "-------------------------------"
    echo "starting experiment loops: ${s}"
    ./bench1  "$(pwd)/dejavu_platform.xml" ${s}  > ${logDir}/sg_${s}.log 2>&1
    echo "done"

    awk -f parse.awk "${logDir}/sg_${s}.log" > "${resultsDir}/${resF}_${s}.csv"

    tail -n+1 "${resultsDir}/${resF}_${s}.csv" >> "${resultsDir}/${resF}.csv"

done
