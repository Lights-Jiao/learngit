#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pika

# connect to local rabbit mq
conn = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
channel = conn.channel()

# declare a queue
channel.queue_declare(queue='hello')

# declare call back func
def call_back(ch, method, properties, body):
    print(" [x] received %r" % body)


channel.basic_consume(call_back,
                      queue='hello',
                      no_ack=True)

print(" [*] waiting for message. to exit press ctrl+c")
channel.start_consuming()
