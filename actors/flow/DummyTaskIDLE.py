import time
import random
import threading

from pypapi import events, papi_high as high

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
        self.tasks = []
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

    @condition(['token','spIn'],[])
    def token_available(self, token, spIn):
        calvinsys.write(self.log, self.name+" received "+str(time.time()))
        if(spIn == "none"):
            spOut = self.tracer.start_span("compute_"+str(self.tracer.service_name))
        else:
            spOut = self.tracer.start_span('ChildSpan'+str(self.tracer.service_name), child_of=spIn)
            spIn.finish()

        x = threading.Thread(target=self.thread_test, args=(token, spOut))
        x.start()
        #self.tasks.append({'token': token, 'timer': self.delay,'span': spOut})
#        s=" finished: "
#        for i in self.timers:
#            s+=str(calvinsys.can_read(i["timer"]))
        calvinsys.write(self.log, self.name+" timers size"+str(len(self.tasks)))

    def thread_test(self, token, span):
        t_begin = time.time()
        high.start_counters([events.PAPI_TOT_INS,])
        for i in range(self.delay):
            continue
        self.tasks.append({'token':token, 'timer':self.delay, 'span': span})
        x=high.stop_counters()
        dur = time.time() - t_begin
        calvinsys.write(self.log, self.name+"finished loop. iter: "+str(self.delay)+" dur: "+str(dur)+" instcnt: "+str(x))
        
    @stateguard(lambda self: len(self.tasks) > 0) # and calvinsys.can_read(self.timers[0]['timer']))
    @condition([], ['token','spOut'])
    def car(self):
        item = self.tasks.pop(0)
        return ("a"*self.size, item['span'])

    action_priority = (token_available, car)
    requires = ['sys.timer.once']
