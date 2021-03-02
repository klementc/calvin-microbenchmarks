FROM ubuntu

RUN apt-get update
RUN apt-get install -y python-setuptools python-dev build-essential python3-pip

RUN pip3 install --upgrade pip
RUN pip3 install jaeger-client
RUN pip3 install pika
RUN pip3 install numpy

RUN mkdir /expeFiles
ADD computeService.py /expeFiles
ADD dataSourceService.py /expeFiles
ADD deployInfra.sh /expeFiles
ADD launchCalib.sh /expeFiles
ADD parse.awk /expeFiles
ADD sinkService.py /expeFiles
ADD tsCal.csv /expeFiles
ADD launchOnce.sh /expeFiles
ADD default5TimeStamps.csv /expeFiles