#!/bin/bash

# run this script to perform the load test on your machine/swarm once it is deployed
# important parameters: start, incr, end to modify the load used

# exec run
[ -z "${resF}" ] && resF="results"
[ -z "${outputDir}" ] && outputDir="./out"
[ -z "${start}" ] && start="50"
[ -z "${end}" ] && end="1000"
[ -z "${incr}" ] && incr="50"
[ -z "${nbSample}" ] && nbSample=1
[ -z "${summaryFile}" ] && summaryFile="summaryPetClinic.csv"


if [[ -z "${JMETER_DIR}" ]]
then
  echo "You must specify the path to your jmeter executable in JMETER_DIR variable"
  exit 1
fi

if [[ -z "${JMETER_LOADS_DIR}" ]]
then
  echo "You must specify the path to your jmeter loads directory in JMETER_LOADS_DIR variable"
  exit 1
fi

if [[ ! -e ${outputDir} ]]
then
    mkdir -p ${outputDir}
fi

if [[ ! -e ${summaryFile} ]]
then
    echo "load,sample,throughput,meanLatency,medianLatency" > ${summaryFile}
fi


echo "Launch loads from ${start} to ${end} by step ${incr} into ${outputDir}"
set -x
for load in `seq ${start} ${incr} ${end}`
do
  for sample in `seq 1 1 ${nbSample}`
  do
    ${JMETER_DIR}/jmeter -n -t ${JMETER_LOADS_DIR}/loadTest_${load}.jmx -l ${outputDir}/out_${load}_s${sample}.csv -e -o ${outputDir}/out_${load}_s${sample}

    # get summary values and append them to ${summaryFile}
    throughput=`jq '."All Owners".throughput' ${outputDir}/out_${load}_s${sample}/statistics.json`
    meanResTime=`jq '."All Owners".meanResTime' ${outputDir}/out_${load}_s${sample}/statistics.json`
    medianResTime=`jq '."All Owners".medianResTime' ${outputDir}/out_${load}_s${sample}/statistics.json`

    echo "${load},${sample},${throughput},${meanResTime},${medianResTime}" >> ${summaryFile}

    sleep 10
  done
done