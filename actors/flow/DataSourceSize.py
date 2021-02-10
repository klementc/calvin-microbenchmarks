from calvin.actor.actor import Actor, manage, condition


class DataSourceSize(Actor):

    """
    Divides input on port 'dividend' with input on port 'divisor'
    Inputs :
        trigger
    Output :
        mailboxOut2
    """

    @manage(['size'])
    def init(self, size):
        self.size = size

    @condition(action_input=['trigger'], action_output=['mailboxOut2'])
    def createData(self, trigger):
        data = bytearray(self.size)
        
        return (data,)

    action_priority = (createData,)
