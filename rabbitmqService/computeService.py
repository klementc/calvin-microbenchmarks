#!/usr/bin/env python

import argparse
import pika, sys, os
import threading
import json
import opentracing
import time

from jaeger_client import Config
from opentracing import Tracer, Format



def main(args):
    print(" [x] Starting service, mq host: %r, input: %r, output: %r"%(args.rmqHost, args.inputMB, args.outputMB))
    connection = pika.BlockingConnection(pika.ConnectionParameters(host=args.rmqHost))
    channelIn = connection.channel()
    channelIn.queue_declare(queue=args.inputMB)
    config = Config(
        config={ # usually read from some yaml config
            'sampler': {
                'type': 'const',
                'param': 1,
            },
            'logging': True,
        },
        service_name=args.sName,
    )
    tracer = config.new_tracer()
    
    def callback(ch, method, properties, body):
        recTS = time.time()
        ts = float(body.decode())
        diff = recTS - ts
        print(" [%r] Received (transmission: %r )" %(args.sName, diff,))

        # extract or create span
        # https://opentracing.io/docs/best-practices/instrumenting-frameworks/
        try:
            span_ctx = tracer.extract(Format.TEXT_MAP, properties.headers)
            sp = tracer.start_span(operation_name='sink',
                                      references=opentracing.child_of(span_ctx))
        except opentracing.propagation.InvalidCarrierException:
            sp = tracer.start_span(operation_name="compute")
        x = threading.Thread(target=thread_exec, args =(sp,recTS,))
        x.start()

    def thread_exec(sp, recTS):
        execTS = time.time()
        print("[%r] Start executing the request at time %r (waited %r)"%(args.sName, execTS, execTS-recTS,))
        for i in range(int(args.computeCost)):
            continue
        #https://github.com/pika/pika/issues/511
        connection = pika.BlockingConnection(pika.ConnectionParameters(host=args.rmqHost))
        co = connection.channel()
        co.queue_declare(queue=args.outputMB)

        h = {}
        tracer.inject(sp,opentracing.Format.HTTP_HEADERS, h)
        co.basic_publish(exchange='', routing_key=args.outputMB, properties=pika.BasicProperties(headers=h), body=str(time.time()))
        sp.finish()
        print("[%r] Finished executing the request at time %r (total time %r)"%(args.sName, time.time(), time.time()-recTS))


    channelIn.basic_consume(queue=args.inputMB, on_message_callback=callback, auto_ack=True)

    print(' [%r] Waiting for Requests. To exit press CTRL+C'%(args.sName))
    channelIn.start_consuming()

if __name__ == '__main__':
    try:
        parser = argparse.ArgumentParser()
        # Adding optional argument
        parser.add_argument("-r", "--rmqHost", help = "RabbitMQ host", required=True)
        parser.add_argument("-i", "--inputMB", help = "RabbitMQ input queue (queue to receive requests)", required=True)
        parser.add_argument("-o", "--outputMB", help = "RabbitMQ output queue (queue to output results)", required=True)
        parser.add_argument("-n", "--sName", help = "Service name", required=True)        
        parser.add_argument("-c", "--computeCost", help = "Iterations amount", required=True)        

        # Read arguments from command line
        args = parser.parse_args()
        
        main(args)
    except KeyboardInterrupt:
        print('Interrupted')
        try:
            sys.exit(0)
        except SystemExit:
            os._exit(0)


