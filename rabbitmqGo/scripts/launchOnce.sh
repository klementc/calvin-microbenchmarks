#!/bin/bash

# launch locally (1 node) services of bench infrastructures
[ -z "${N1COST}" ] && N1COST="10000"
[ -z "${N2COST}" ] && N2COST="10000"
[ -z "${logDir}" ] && logDir="/logs/"
[ -z "${hostLogPath}" ] && hostLogPath="${HOME}/logs_expe/goLogs/"
[ -z "${suffix}" ] && suffix="DEFAULT"
[ -z "${rootCode}" ] && rootCode="../"
[ -z "${tsFile}" ] && tsFile="../../rabbitmqService/tsCal.csv"
[ -z "${parD}" ] && parD="25"
[ -z "${hostMQ}" ] && hostMQ="amqp://guest:guest@localhost:5672/"
[ -z "${firstCore}" ] && firstCore=2

if [[ -z ${scenario} ]]
then
    echo "Indicate the scenario to launch for launchOnce.sh to run"
    exit 1
fi

if [[ -z ${logDir} ]]
then
    mkdir -p ${logDir}
fi


# IMPORTANT: remove previous services
echo "Kill previous services and deploy infrastructure (deployInfra.sh)"
bash deployInfra.sh kill
sleep 10
echo "Launch infrastructure with scenario ${scenario}"
firstCore=${firstCore} hostLogPath=${hostLogPath} parD=${parD} hostMQ=${hostMQ} suffix=${suffix} logDir=${logDir} N1COST=${N1COST} scenario=${scenario} bash deployInfra.sh
sleep 10
echo "Launch datasource"
./${rootCode}/senderService -s "scenario${scenario}" -r ${hostMQ} -o serv1 -t ${tsFile} 2>&1 | tee ${logDir}/${scenario}_DS_${N1COST}_${suffix}.log


echo "Datasource sent all of its messages, parse resulting logs for scenario ${scenario}"
if [[ ${scenario} = "1"]]
then
    awk -f parse.awk "${logDir}/1_S1_${N1COST}_${suffix}.log" > "${logDir}/results_1_${N1COST}_${suffix}.csv"
elif [[ ${scenario} = "2" ]]
then
    awk -f parse.awk "${logDir}/2_S1_${N1COST}_${suffix}.log" > "${logDir}/results_2_${N1COST}_${N2COST}_${suffix}.csv"
    awk -f parse.awk "${logDir}/2_S2_${N2COST}_${suffix}.log" > "${logDir}/results_2_${N1COST}_${N2COST}_${suffix}.csv"
else
    echo "UNKNOWN SCENARIO '${scenario}', cannot parse"
fi