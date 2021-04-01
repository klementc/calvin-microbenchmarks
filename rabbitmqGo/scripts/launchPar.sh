#!/bin/bash

# launch locally (1 node) services of bench infrastructures
[ -z "${logDir}" ] && logDir="/logs/"
[ -z "${suffix}" ] && suffix="DEFAULT"
[ -z "${hostLogPath}" ] && hostLogPath="${HOME}/logs_expe/goLogs/"
[ -z "${parD}" ] && parD="10"

[ -z "${start}" ] && start=1000000
[ -z "${iter}" ] && iter=5000000
[ -z "${end}" ] && end=10000000
[ -z "${nbSamples}" ] && nbSamples=3
[ -z "${firstCore}" ] && firstCore=1
[ -z "${durIter}" ] && durIter=360

if [[ -z ${scenario} ]]
then
    echo "Unknown scenarion, you need to specify it"
    exit 1
fi
if [[ -z ${tsFile} ]]
then
    echo "You need to specify a timestamp file (on the container)"
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
echo "serviceName,nbIter,timestamp,totDurInServ,computeDur,parExec,totReqProcessed,scenario" > "${hostLogPath}/${scenario}_aggrResults_${start}-${iter}-${end}_${nbSamples}.csv"

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

        # launch experiment (set first core according to scenario)
        if [[ ${scenario} = 1 ]]
        then
            # 2 full cores required for this scenario
            fc=$((${firstCore}+2*(${sample}-1)))
            echo "Scenario 1, sample ${sample} first core = ${fc}"
            # launch datasource (N1COST only)r
            firstCore=${firstCore} hostLogPath=${hostLogPath} parD=${parD} hostMQ=${hostMQ} N1COST=${s} suffix=${suffix}_${sample} logDir=${logDir} tsFile=${tsFile} scenario=${scenario} bash launchOnce.sh &
        elif [[ ${scenario} = 2 ]]
        then
            # 3 full cores required for this scenario
            fc=$((${firstCore}+3*(${sample}-1)))
            echo "Scenario 1, sample ${sample} first core = ${fc}"
            # launch datasource (N1COST = N2COST)
            durIter=${durIter} firstCore=${firstCore} hostLogPath=${hostLogPath} parD=${parD} hostMQ=${hostMQ} N1COST=${s} N2COST=${s} suffix=${suffix}_${sample} logDir=${logDir} tsFile=${tsFile} scenario=${scenario} bash launchOnce.sh &
        else
            echo "Scenario ${scenario} does not exist, exit"
            exit 1
        fi

    done

    # wait for the end
    sleep ${durIter}
    # destroy containers
    docker stop $(docker ps -q) ; docker rm $(docker ps -aq)
    docker system prune --volumes -f
    # gather results
    for sample in `seq 1 ${nbSamples}`
    do
        tail -n+2 "${hostLogPath}/results_${s}_${scenario}_${suffix}_${sample}.csv" >> "${hostLogPath}/${scenario}_aggrResults_${start}-${iter}-${end}_${nbSamples}.csv"
        echo "done"
    done

done
