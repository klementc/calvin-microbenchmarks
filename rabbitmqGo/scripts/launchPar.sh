#!/bin/bash

# launch locally (1 node) services of bench infrastructures
[ -z "${N1COST}" ] && N1COST="10000000"
[ -z "${logDir}" ] && logDir="./logs/"
[ -z "${suffix}" ] && suffix="DEFAULT"
[ -z "${tsFile}" ] && tsFile="../../rabbitmqService/tsCal.csv"
[ -z "${hostLogPath}" ] && hostLogPath="${HOME}/logs_expe/goLogs/"
[ -z "${parD}" ] && parD="25"

[ -z "${start}" ] && start=1000000
[ -z "${iter}" ] && iter=5000000
[ -z "${end}" ] && end=10000000
[ -z "${nbSamples}" ] && nbSamples=3
[ -z "${firstCore}" ] && firstCore=2
[ -z "${durIter}" ] && durIter=320

if [[ ! -e ${scenario} ]]
then
    echo "Unknown scenarion, you need to specify it"
    exit 1
fi


if [[ ! -e ${hostLogPath} ]]
then
    mkdir -p ${hostLogPath}
fi

echo "Launching calibration:"
echo " ${nbSamples} executions per value"
echo " value start: ${start} end: ${end} incr: ${iter}"

#header of aggregated results file
echo "serviceName,nbIter,timestamp,totDurInServ,computeDur,parExec,totReqProcessed,scenario" > "${hostLogPath}/aggrResults_${start}-${iter}-${end}_${nbSamples}.csv"

rmqPort1=5672
rmqPort2=15672
hostMQTemplate="amqp://guest:guest@localhost:"

for s in `seq ${start} ${iter} ${end}`
do
    echo "--------------------"
    echo "new Loop value: ${s}"
    for sample in `seq 1 ${nbSamples}`
    do
	rmqPort1E=$((${sample}+${rmqPort1}))
	rmqPort2E=$((${sample}+${rmqPort2}))
	hostMQ="${hostMQTemplate}${rmqPort1E}"
	echo "Launch rabbitmq docker container on localhost and jaeger ${hostMQ} ${rmqPort2E} ${rmqPort1E}"
	docker run -d -p ${rmqPort2E}:15672 -p ${rmqPort1E}:5672 --hostname my-rabbit rabbitmq:3
	sleep 2

	# launch experiment
	#docker run -d -v ${hostLogPath}:/logs --cpus=1.0 --cpuset-cpus=$((${firstCore}+${sample})) -e cpuload=100 --network host --rm -ti expe/rmqgo:latest /bin/bash -c "cd scripts ; parD=${parD} hostMQ=${hostMQ} N1COST=${s} suffix=${suffix}_${sample} logDir=${logDir} tsFile=${tsFile} scenario=${scenario} bash launchOnce.sh"
    hostLogPath=${hostLogPath} parD=${parD} hostMQ=${hostMQ} N1COST=${s} suffix=${suffix}_${sample} logDir=${hostLogPath} tsFile=${tsFile} scenario=${scenario} bash launchOnce.sh
    done

    # wait for the end
    sleep ${durIter}
    # destroy containers
    docker stop $(docker ps -q) ; docker rm $(docker ps -aq)
    docker system prune --volumes -f
    # gather results
    for sample in `seq 1 ${nbSamples}`
    do
	tail -n+2 "${hostLogPath}/results_${s}_${suffix}_${sample}.csv" >> "${hostLogPath}/${scenario}_aggrResults_${start}-${iter}-${end}_${nbSamples}.csv"
	echo "done"
    done

done
