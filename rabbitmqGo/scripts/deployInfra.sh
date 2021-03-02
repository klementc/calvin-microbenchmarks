#!/bin/bash

# launch locally (1 node) services of bench infrastructures
[ -z "${N1COST}" ] && N1COST="10000000"
[ -z "${logDir}" ] && logDir="./logs/"
[ -z "${suffix}" ] && suffix="DEFAULT"
[ -z "${rootCode}" ] && rootCode="../"
#[ -z "${expID}" ]  && expID=`date +%Y-%m-%d_%H-%M-%S`
if [[ ! -e ${logDir} ]]
then
    mkdir -p ${logDir}
fi

# kill already launched application
if [[ $1 = "kill" ]]
then
    pkill -9 -f computeService.go
    pkill -9 -f sinkService.go
# launch the most simple application with only 1 service
elif [[ $1 = "1" ]]
then
    echo "Configuration 1: 1 service -> 1 sink (then plug-in the source to queue 'computeTask' start)"
    # compute service
    go run ${rootCode}/cmd/computeService/computeService.go -i serv1 -o sink -n computeService1 -c 5000000000 2>&1 | tee ${logDir}/1_S1_${suffix}.log &
    # sink service
    go run ${rootCode}/cmd/sinkService/sinkService.go -i sink -n sinkServ 2>&1 | tee ${logDir}/1_Sink_${suffix}.log &
    echo "Application ready to start. Create a dataSource on queue serv1"
# add elif cases for future infrastructures
fi
