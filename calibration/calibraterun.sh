#!/bin/bash

tickInter=10
duration=60
templateF="testCalibTemplate.calvin"

calvinFilesDir="calvinFiles/"
calvinLogDir="calvinLogs/"

resF="results.csv"
echo "iter, dur, instcnt" > ${resF}
#vals=(1 1000 10000 100000 1000000 2500000 5000000 7500000 10000000 20000000)
echo "Calibration runs:"
echo "tickInterval: ${tickInter}"
echo "duration: ${duration}"
echo "template script: ${templateF}"

if [[ ! -e ${calvinFilesDir} ]]
then
    mkdir ${calvinFilesDir}
fi
if [[ ! -e ${calvinLogDir} ]]
then
    mkdir ${calvinLogDir}
fi


for s in `seq 1 100000 5000000` # "${vals[@]}"
do
   fcalv="${calvinFilesDir}/calib_${s}_${tickInter}.calvin"
   export s
   export tickInter
   echo "------------------"
   echo "Loop with size: $s"
   echo "Output to: $fname"
   envsubst < ${templateF} > ${fcalv}

   # deploy runtimes
   prefix="${calvinLogDir}" suffix="${s}" bash deploy_runtimes.sh up
   sleep 5
   
   # deploy app
   bash deploy_runtimes.sh app ${fcalv}
   #   csruntime --host localhost ${fcalv} -w 60 -f ${fname}

   sleep ${duration}
   # stop app
   bash deploy_runtimes.sh down
   
   # process log files
   awk -f parse.awk ${calvinLogDir}/${prefix}_runtimelog0_${s} >> ${resF}
   awk -f parse.awk ${calvinLogDir}/${prefix}_runtimelog1_${s} >> ${resF}
   awk -f parse.awk ${calvinLogDir}/${prefix}_runtimelog2_${s} >> ${resF}
   awk -f parse.awk ${calvinLogDir}/${prefix}_runtimelog3_${s} >> ${resF}
   awk -f parse.awk ${calvinLogDir}/${prefix}_runtimelog4_${s} >> ${resF}
done

echo "Analyze results"
Rscript analysis.r
echo "Done :)"
