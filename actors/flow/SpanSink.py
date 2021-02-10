import logging
import time
import random
from calvin.actor.actor import Actor, manage, condition,calvinsys
from jaeger_client import Config

class SpanSink(Actor):

    """
    span sink; close the span and return
    Inputs :
        spIn: input span
    Output :
    """


    @manage(['log','tracer'])
    def init(self):
        self.log = calvinsys.open(self, "log.info")

        config = Config(
            config={ # usually read from some yaml config
                'sampler': {
                    'type': 'const',
                    'param': 1,
                },
                'logging': True,
            },
            service_name='spanSink'+str(random.randint(1,1000)),
            validate=True,
        )
        self.tracer = config.new_tracer()


    @condition(action_input=['spIn'], action_output=[])
    def sinkspan(self, spIn):
        calvinsys.write(self.log, "sink "+str(time.time()))
        if(spIn != None):
            spIn.finish()

        return ()

    action_priority = (sinkspan,)
