#!/usr/bin/env python

import argparse
import pika, sys, os
import threading


def main(args):
    print(" [x] Starting service, mq host: %r, input: %r, output: %r"%(args.rmqHost, args.inputMB, args.outputMB))
    connection = pika.BlockingConnection(pika.ConnectionParameters(host=args.rmqHost))
    channelIn = connection.channel()
    channelIn.queue_declare(queue=args.inputMB)
#    channelOut = connection.channel()
#    channelOut.queue_declare(queue=args.outputMB)

    def callback(ch, method, properties, body):
        print(" [x] Received a task request")
        x = threading.Thread(target=thread_exec)
        x.start()
        #for i in range(100000000):
        #    continue

    def thread_exec():
        print(" [x] Start executing the request %r"%args.outputMB)
        for i in range(100000000):
            continue
        #https://github.com/pika/pika/issues/511
        connection = pika.BlockingConnection(pika.ConnectionParameters(host=args.rmqHost))
        co = connection.channel()
        co.queue_declare(queue=args.outputMB)

        co.basic_publish(exchange='', routing_key=args.outputMB, body='Hello World!')


    channelIn.basic_consume(queue=args.inputMB, on_message_callback=callback, auto_ack=True)

    print(' [*] Waiting for Requests. To exit press CTRL+C')
    channelIn.start_consuming()

if __name__ == '__main__':
    try:
        parser = argparse.ArgumentParser()
        # Adding optional argument
        parser.add_argument("-r", "--rmqHost", help = "RabbitMQ host", required=True)
        parser.add_argument("-i", "--inputMB", help = "RabbitMQ input queue (queue to receive requests)", required=True)
        parser.add_argument("-o", "--outputMB", help = "RabbitMQ output queue (queue to output results)", required=True)        
        # Read arguments from command line
        args = parser.parse_args()
        
        main(args)
    except KeyboardInterrupt:
        print('Interrupted')
        try:
            sys.exit(0)
        except SystemExit:
            os._exit(0)


