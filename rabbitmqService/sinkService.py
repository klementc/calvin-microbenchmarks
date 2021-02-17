#!/usr/bin/env python

import argparse
import pika, sys, os
import opentracing
import time
import struct

from jaeger_client import Config
from opentracing import Tracer, Format

def main(args):
    print(" [%r] Starting sink service, mq host: %r, input: %r"%(args.sName, args.rmqHost, args.inputMB))
    connection = pika.BlockingConnection(pika.ConnectionParameters(host='localhost'))
    channel = connection.channel()
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
    channel.queue_declare(queue=args.inputMB)

    def callback(ch, method, properties, body):
        ts = float(body.decode())
        diff = time.time() - ts
        print(" [%r] Received (transmission: %r )" %(args.sName, diff,))
        span_ctx = tracer.extract(Format.TEXT_MAP, properties.headers)
        print(span_ctx)
        child = tracer.start_span(operation_name='sink',
                              references=opentracing.child_of(span_ctx))
        child.finish()

    channel.basic_consume(queue=args.inputMB, on_message_callback=callback, auto_ack=True)

    print(' [%r] Sink waiting for messages. To exit press CTRL+C'%(args.sName))
    channel.start_consuming()

if __name__ == '__main__':
    try:
        parser = argparse.ArgumentParser()
        # Adding optional argument
        parser.add_argument("-r", "--rmqHost", help = "RabbitMQ host", required=True)
        parser.add_argument("-i", "--inputMB", help = "RabbitMQ input queue (queue to receive requests)", required=True)
        parser.add_argument("-n", "--sName", help = "Service name", required=True)        

        # Read arguments from command line
        args = parser.parse_args()

        main(args)
    except KeyboardInterrupt:
        print('Interrupted')
        try:
            sys.exit(0)
        except SystemExit:
            os._exit(0)

