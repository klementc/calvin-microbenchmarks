#!/usr/bin/env python
import pika
import argparse


parser = argparse.ArgumentParser()
# Adding optional argument
parser.add_argument("-r", "--rmqHost", help = "RabbitMQ host", required=True)
parser.add_argument("-o", "--outputMB", help = "RabbitMQ output queue", required=True)        
# Read arguments from command line
args = parser.parse_args()



connection = pika.BlockingConnection(
    pika.ConnectionParameters(host=args.rmqHost))
channel = connection.channel()

channel.queue_declare(queue=args.outputMB)

channel.basic_publish(exchange='', routing_key=args.outputMB, body='Hello World!')
print(" [x] Sent request")
connection.close()
