import logging
import time
from calvin.actor.actor import Actor, manage, condition,calvinsys
from jaeger_client import Config

class DummyTask(Actor):

    """
    perform dummy task
    Inputs :
        mailboxIn: input data mailbox
    Output :
        mailboxOut: out mailbox
    """


    @manage(['size', 'dur', 'log','tracer'])
    def init(self, size, dur):
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
            service_name='your-app-name',
            validate=True,
        )
        self.tracer = config.initialize_tracer()
        

    @condition(action_input=['mailboxIn'], action_output=['mailboxOut'])
    def computeAndReturn(self, data):
        sp = self.tracer.start_span("coucou")
            
        sp.log_kv({'event': 'test message', 'life': 42})
        calvinsys.write(self.log, "start exec"+str(time.time()))
        t_end = time.time() + self.dur/1000
        data = bytearray(self.size)
        while time.time() < t_end:
            continue
        calvinsys.write(self.log, "finished exec"+str(time.time()))
        sp.finish()
        return (data,)

    action_priority = (computeAndReturn,)
