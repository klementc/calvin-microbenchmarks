#!/usr/bin/env python
import pika
import argparse
import time
import numpy as np
import logging

# logger config

logger = logging.getLogger('log_computetask')
#logger.basicConfig(stream=sys.stdout, level=logging.INFO)
logger.setLevel(logging.INFO)
ch = logging.StreamHandler()
ch.setLevel(logging.INFO)
formatter = logging.Formatter('%(asctime)s - %(levelname)s - %(message)s')
ch.setFormatter(formatter)
logger.addHandler(ch)


parser = argparse.ArgumentParser()
# Adding optional argument
parser.add_argument("-r", "--rmqHost", help = "RabbitMQ host", required=True)
parser.add_argument("-o", "--outputMB", help = "RabbitMQ output queue", required=True)
parser.add_argument("-n", "--sName", help = "Service name", required=True)        

# Read arguments from command line
args = parser.parse_args()



connection = pika.BlockingConnection(
    pika.ConnectionParameters(host=args.rmqHost))
channel = connection.channel()

channel.queue_declare(queue=args.outputMB)
#for i in np.arange (0.25, 0.07, -0.005):
#    for j in range (10):
#        channel.basic_publish(exchange='', routing_key=args.outputMB, body=str(time.time()))
#        print(" [x] Sent request")
#        time.sleep (i)
#    time.sleep(3)

def trigger():
    logger.info("%s Source send request at time %r"%(args.sName, time.time()))
    channel.basic_publish(exchange='', routing_key=args.outputMB, body=str(time.time()))

def periodicTrigger(period, nbReq):
    logger.info( "%s Periodic trigger start: p=%r, nbReq=%r"%(args.sName, period, nbReq))
    for i in range(nbReq):
        time.sleep(period)
        trigger()

def timeStampFileTrigger(fp):
    with open(fp) as fo:
        lines = [float(line.rstrip()) for line in fo]
        print(lines)
        start = time.time()
        for i in lines:
            diff = start+i-time.time()
            if(diff>0):
                time.sleep(diff)
            trigger()
        

nbP = 20
timeStampFileTrigger("default5TimeStamps.csv")
#for p in np.arange(.25, .07, -.005):
#    periodicTrigger(p, nbP)
#    time.sleep(5)




logger.info("%r Source finished, exit")
connection.close()
