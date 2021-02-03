import time
import random

from calvin.actor.actor import Actor, manage, condition, stateguard, calvinsys
from jaeger_client import Config


class DummyTaskIDLE(Actor):
    """
    Sends input on after a given delay has passed with jaeger tracing. Preserves time between tokens.

    Inputs :
        token : anything
        spIn : span input
    Outputs:
        token : anything
        spOut: span output
    """

    @manage(['delay', 'size', 'name', 'timers', 'log','tracer'])
    def init(self, delay, size, servName):
        self.delay = delay
        self.size = size
        self.log = calvinsys.open(self, "log.info")
        self.name = servName
        self.timers = []
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

        
    def new_timer(self):
        timer = calvinsys.open(self, "sys.timer.once", period=self.delay)
        return timer

    @condition(['token','spIn'])
    def token_available(self, token, spIn):
        calvinsys.write(self.log, self.name+" received "+str(time.time()))
        if(spIn == "none"):
            spOut = self.tracer.start_span("compute_"+str(self.tracer.service_name))
        else:
            spOut = self.tracer.start_span('ChildSpan'+str(self.tracer.service_name), child_of=spIn)
            spIn.finish()

        self.timers.append({'token': token, 'timer': self.new_timer(),'span':spOut})
        calvinsys.write(self.log, self.name+" timers size"+str(len(self.timers)))

    @stateguard(lambda self: len(self.timers) > 0 and calvinsys.can_read(self.timers[0]['timer']))
    @condition([], ['token','spOut'])
    def timeout(self):
        calvinsys.write(self.log, self.name+" finished exec"+str(time.time()))
        item = self.timers.pop(0)
        calvinsys.read(item['timer'])
        calvinsys.close(item['timer'])
        return (item['token'], item['span'])

    action_priority = (timeout, token_available)
    requires = ['sys.timer.once']
