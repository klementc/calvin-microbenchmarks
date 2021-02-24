#!/usr/bin/awk -f

BEGIN {
#    print ("service, txDur, servDur,wait,nbIter")
}

NR == 4 {
    DELTA = $9
#    print("substract delta from ts:"$9)
}

/INFO compute fin req/{
    print($19","$9 - DELTA","$5","$13","$11","$15","$17","$21)
}

/INFO sink Received/{
    print($13","$9","$5","$11",0,0,NaN,0")
}

END {
}
