#!/bin/bash

# launch locally (1 node) services of bench infrastructures
[ -z "${N1COST}" ] && N1COST="10000000"
[ -z "${N2COST}" ] && N2COST="1000000"
[ -z "${logDir}" ] && logDir="./logs/"
[ -z "${suffix}" ] && suffix="x"

if [[ ! -e ${logDir} ]]
then
    mkdir -p ${logDir}
fi


if [[ $1 = "1" ]]
then
    ulimit -n 30000 # 30,000 open files allowed (might be useful when the load is important)
    echo "Configuration 1: 1 service -> 1 sink (then plug-in the source to queue 'computeTask' start)"
    python -u computeService.py -r localhost -i computeTask -o sink -n compute -c ${N1COST} 2>&1 | tee "${logDir}/1_S1_${suffix}.log" &
    python -u sinkService.py -r localhost -i sink -n sink 2>&1 | tee > "${logDir}/1_Sink_${suffix}.log" &
elif [[ $1 = "2" ]]
then
    ulimit -n 30000 # 30,000 open files allowed (might be useful when the load is important)
    echo "Configuration 2: 1 service -> 1 service -> 1 sink (then plug-in the source to queue 'computeTask' start)"
    python -u computeService.py -r localhost -i computeTask -o computeTask2 -n compute -c ${N1COST} 2>&1 | tee "${logDir}/2_S1_${suffix}.log" &
    python -u computeService.py -r localhost -i computeTask2 -o sink -n compute -c ${N2COST} 2>&1 | tee "${logDir}/2_S2${suffix}.log"
    python -u sinkService.py -r localhost -i sink -n sink 2>&1 | tee "${logDir}/2_Sink.log"
elif [[ $1 = "kill" ]]
then
     echo "kill running services and sinks"
     pkill -9 -f sinkService.py
     pkill -9 -f computeService.py
     pkill -9 -f dataSourceService.py
fi
