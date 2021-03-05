#!/bin/bash

# exec run
[ -z "${resF}" ] && resF="results"
[ -z "${logDir}" ] && logDir="./execLogs"
[ -z "${start}" ] && start="20000000"
[ -z "${end}" ] && end="50000000"
[ -z "${incr}" ] && incr="2000000"
[ -z "${tsFile}" ] && tsFile="default5TimeStamps.csv"

if [[ ! -e ${logDir} ]]
then
    mkdir -p ${logDir}
fi


echo "ts,qArr,instArr,startEx,endEx,flops" > "${logDir}/${resF}.csv"

for s in `seq ${start} ${incr} ${end}`
do
    suffix="1_${s}"
    echo "ts,qArr,instArr,startEx,endEx,flops" > "${logDir}/${resF}_${s}.csv"
    echo "$(pwd)/dejavu_platform.xml"
    echo "-------------------------------"
    echo "starting experiment loops: ${s}"
    ./bench1  "$(pwd)/dejavu_platform.xml" ${s} ${tsFile} > ${logDir}/sg_${s}.log 2>&1
    echo "done"

    awk -f parse.awk "${logDir}/sg_${s}.log" > "${logDir}/${resF}_${s}.csv"

    tail -n+1 "${logDir}/${resF}_${s}.csv" >> "${logDir}/${resF}.csv"

done
