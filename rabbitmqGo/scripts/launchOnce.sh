#!/bin/bash

# launch locally (1 node) services of bench infrastructures
[ -z "${N1COST}" ] && N1COST="10000000"
[ -z "${logDir}" ] && logDir="./logs/"
[ -z "${suffix}" ] && suffix="DEFAULT"
[ -z "${rootCode}" ] && rootCode="../"
[ -z "${tsFile}" ] && tsFile="../../rabbitmqService/tsCal.csv"
#[ -z "${expID}" ]  && expID=`date +%Y-%m-%d_%H-%M-%S`

if [[ ! -e ${logDir} ]]
then
    mkdir -p ${logDir}
fi


# IMPORTANT: remove previous services
echo "kill previous services and deploy infrastructure (deployInfra.sh 1)"
bash deployInfra.sh kill
suffix=${suffix} logDir=${logDir} N1COST=${N1COST} bash deployInfra.sh 1

echo "launch datasource"
go run ${rootCode}/cmd/dataSourceService/senderService.go -o serv1 -t ${tsFile} 2>&1 | tee ${logDir}/1_DS_${N1COST}_${suffix}.log 

echo "datasource sent all of its messages, parse resulting logs"
awk -f parse.awk "${logDir}/1_S1_${N1COST}_${suffix}.log" > "${logDir}/results_${N1COST}_${suffix}.csv"
