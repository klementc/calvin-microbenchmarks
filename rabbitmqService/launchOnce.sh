#!/bin/bash

# launch locally (1 node) services of bench infrastructures
[ -z "${N1COST}" ] && N1COST="10000000"
[ -z "${N2COST}" ] && N2COST="1000000"
[ -z "${logDir}" ] && logDir="./logs/"
[ -z "${suffix}" ] && suffix=`date +%Y-%m-%d_%H-%M-%S`
#[ -z "${expID}" ]  && expID=`date +%Y-%m-%d_%H-%M-%S`

suffix=${suffix} logDir=${logDir} N1COST=${N1COST} bash deployInfra.sh 1
python3 dataSourceService.py -r localhost -o computeTask -n source -t ./tsCal.csv -e ${suffix} #${expID}

awk -f parse.awk "${logDir}/1_S1_${suffix}.log" > "${logDir}/results_${N1COST}_${suffix}.csv"
