#!/bin/sh

# just used to generate jmx files with various loads
outDir=JMXFiles

[ ! -e "${outDir}" ] && mkdir -p ${outDir}

for load in `seq 50 50 4000`
do
  awk -v loadJMX="$load" -f template.awk loadTest_template.jmx >> ${outDir}/loadTest_${load}.jmx
done
