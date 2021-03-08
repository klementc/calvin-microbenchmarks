#!/bin/bash

# launch locally (1 node) services of bench infrastructures
[ -z "${N1COST}" ] && N1COST="10000000"
[ -z "${logDir}" ] && logDir="./logs/"
[ -z "${suffix}" ] && suffix="DEFAULT"
[ -z "${rootCode}" ] && rootCode="../"
[ -z "${hostMQ}" ] && hostMQ="amqp://guest:guest@localhost:5672/"
[ -z "${parD}" ] && parD="25"
#[ -z "${expID}" ]  && expID=`date +%Y-%m-%d_%H-%M-%S`

# kill already launched application
if [[ $1 = "kill" ]]
then
    pkill -9 -f computeService.go
    pkill -9 -f sinkService.go
    pkill -9 computeService
    pkill -9 sinkService
# launch the most simple application with only 1 service
elif [[ $1 = "1" ]]
then
    if [[ ! -e ${logDir} ]]
    then
	mkdir -p ${logDir}
    fi

    echo "Configuration 1: 1 service -> 1 sink (then plug-in the source to queue 'computeTask' start)"
    # compute service
    #    go run ${rootCode}/cmd/computeService/computeService.go -r ${hostMQ} -i serv1 -o sink -n computeService1_${suffix} -c ${N1COST} 2>&1 | tee ${logDir}/1_S1_${N1COST}_${suffix}.log &
    ./${rootCode}/computeService -r ${hostMQ} -i serv1 -o sink -n computeService1_${suffix} -c ${N1COST} -p ${parD} 2>&1 | tee ${logDir}/1_S1_${N1COST}_${suffix}.log &
    # sink service
    #    go run ${rootCode}/cmd/sinkService/sinkService.go -r ${hostMQ} -i sink -n sinkServ 2>&1 | tee ${logDir}/1_Sink_${N1COST}_${suffix}.log &
    ./${rootCode}/sinkService -r ${hostMQ} -i sink -n sinkServ 2>&1 | tee ${logDir}/1_Sink_${N1COST}_${suffix}.log &
    echo "Application ready to start. Create a dataSource on queue serv1"
# add elif cases for future infrastructures
fi
