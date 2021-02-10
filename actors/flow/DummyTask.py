import logging
import time
import random

from calvin.actor.actor import Actor, manage, condition,calvinsys
from jaeger_client import Config

class DummyTask(Actor):

    """
    perform dummy task
    Inputs :
        mailboxIn: input data mailbox
        spIn: input span
    Output :
        mailboxOut: out mailbox
        spOut: output span
    """


    @manage(['size', 'dur', 'log','tracer'])
    def init(self, size, dur, servName):
        self.size = size
        self.dur = dur
        self.log = calvinsys.open(self, "log.info")

        config = Config(
            config={ # usually read from some yaml config
                'sampler': {
                    'type': 'const',
                    'param': 1,
                },
                'logging': True,
            },
            service_name=servName,
            validate=True,
        )
        self.tracer = config.new_tracer()


    @condition(action_input=['mailboxIn', 'spIn'], action_output=['mailboxOut', 'spOut'])
    def computeAndReturn(self, data, spIn):

        if(spIn == "none"):
            spOut = self.tracer.start_span("compute_"+str(self.tracer.service_name))
        else:
            spOut = self.tracer.start_span('ChildSpan'+str(self.tracer.service_name), child_of=spIn)
            spIn.finish()

        spOut.log_kv({'event': 'test message', 'life': 42})
        calvinsys.write(self.log, "start exec"+str(time.time()))
        t_end = time.time() + self.dur/1000
        data = bytearray(self.size)
        while time.time() < t_end:
            continue
        calvinsys.write(self.log, "finished exec"+str(time.time()))
#        spOut.finish()
        return (data,spOut)

    action_priority = (computeAndReturn,)
