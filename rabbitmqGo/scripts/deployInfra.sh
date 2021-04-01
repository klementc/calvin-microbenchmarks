#!/bin/bash

[ -z "${N1COST}" ] && N1COST="10000000"
[ -z "${N2COST}"] && N2COST="10000000"
[ -z "${logDir}" ] && logDir="./logs/"
[ -z "${suffix}" ] && suffix="DEFAULT"
[ -z "${rootCode}" ] && rootCode="../"
[ -z "${hostMQ}" ] && hostMQ="amqp://guest:guest@localhost:5672/"
[ -z "${parD}" ] && parD="25"

if [[ ! -e ${logDir} ]]
then
mkdir -p ${logDir}
fi

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

    echo "Configuration 1: DS -> S1 -> Sink (launch DS to queue 'serv1' to start)"
    # compute service
    ./${rootCode}/computeService -r ${hostMQ} -i serv1 -o sink -n S1_${suffix} -c ${N1COST} -p ${parD} 2>&1 | tee ${logDir}/1_S1_${N1COST}_${suffix}.log &
    # sink service
    ./${rootCode}/sinkService -r ${hostMQ} -i sink -n sinkServ 2>&1 | tee ${logDir}/1_Sink_${N1COST}_${suffix}.log &
    echo "Application ready to start. Create a dataSource on queue serv1"

elif [[ $1 = "2" ]]
then
    echo "Configuration 2: DS -> S1 -> S2 -> Sink (launch DS to queue 'serv1' to start)"
    # First compute service (S1)
    ./${rootCode}/computeService -r ${hostMQ} -i serv1 -o serv2 -n S1_${suffix} -c ${N1COST} -p ${parD} 2>&1 | tee ${logDir}/1_S1_${N1COST}_S2_${N2COST}_${suffix}.log &
    # Second compute service (S2)
    ./${rootCode}/computeService -r ${hostMQ} -i serv2 -o sink  -n S2_${suffix} -c ${N2COST} -p ${parD} 2>&1 | tee ${logDir}/1_S2_${N2COST}_S1_${N1COST}_${suffix}.log &
    # sink service
    ./${rootCode}/sinkService -r ${hostMQ} -i sink -n sink 2>&1 | tee ${logDir}/1_Sink_N1_${N1COST}_N2_${N2COST}_${suffix}.log &
    echo "Application ready to start. Create a dataSource on queue serv1"

# add elif cases for future infrastructures
fi
