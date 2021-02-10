#!/bin/bash

tickInter=10
duration=60
templateF="testCalibTemplate.calvin"
resF="results.csv"
echo "iter, dur, instcnt" > ${resF}
vals=(1 1000 10000 100000 1000000 2500000 5000000 7500000 10000000 20000000)
echo "Calibration runs:"
echo "tickInterval: ${tickInter}"
echo "duration: ${duration}"
echo "template script: ${templateF}"

for s in "${vals[@]}"
do
   fname="calib_logs_$s.log"
   fcalv="calib_${s}_${tickInter}.calvin"
   export s
   export tickInter
   echo "------------------"
   echo "Loop with size: $s"
   echo "Output to: $fname"
   envsubst < ${templateF} > "calib_${s}_${tickInter}.calvin"
   csruntime --host localhost ${fcalv} -w 60 -f ${fname}
   awk -f parse.awk ${fname} >> ${resF}
done

echo "Analyze results"
Rscript analysis.r
echo "Done :)"
