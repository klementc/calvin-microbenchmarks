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

echo "ts,service, txDur, servDur,wait,nbIter" > "${resultsDir}/${resF}.csv"

echo "run calibration"


for s in `seq 100000 200000 5000000`
do
    suffix="1_${s}"
    echo "ts,service, txDur, servDur,wait,nbIter" > "${resultsDir}/${resF}_${suffix}.csv"
    bash deployInfra.sh kill

    
    echo "-------------------------------"
    echo "starting experiment loops: ${s}"
    echo "deploy Infrastructure 1..."
    N1COST="${s}" logDir="${logDir}" suffix="${suffix}" bash deployInfra.sh 1
    echo "[x] done"

    echo "launch data source"
    python dataSourceService.py -r localhost -o computeTask -n source

    sleep 10
    echo "-------------------------------"
    echo "finished run, parse results into ${resF}_${suffix}.csv"
    # compute service
    awk -f parse.awk "${logDir}/1_S1_${suffix}.log" > "${resultsDir}/${resF}_${suffix}.csv"
    # sink
    awk -f parse.awk "${logDir}/1_Sink_${suffix}.log" >> "${resultsDir}/${resF}_${suffix}.csv"
    
    echo "append to ${resF}"
    tail -n+1 "${resultsDir}/${resF}_${suffix}.csv" >> "${resultsDir}/${resF}.csv"
done

echo "finished"
