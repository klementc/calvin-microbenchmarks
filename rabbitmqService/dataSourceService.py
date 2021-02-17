#!/usr/bin/env python
import pika
import argparse
import time
import numpy as np

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
    print(" [%r] Source send request at time %r"%(args.sName, time.time()))
    channel.basic_publish(exchange='', routing_key=args.outputMB, body=str(time.time()))

def periodicTrigger(period, nbReq):
    print( "[%r] Periodic trigger start: p=%r, nbReq=%r"%(args.sName, period, nbReq))
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
                time.sleep(start+i-time.time())
            trigger()
        

nbP = 20
timeStampFileTrigger("test.ts")
#for p in np.arange(.25, .07, -.005):
#    periodicTrigger(p, nbP)
#    time.sleep(5)




print("[%r] Source finished, exit")
connection.close()
