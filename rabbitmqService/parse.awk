#!/usr/bin/awk -f

BEGIN {
#    print ("service, txDur, servDur,wait,nbIter")
}


/INFO compute fin req/{
    print($9","$5","$13","$11","$15","$17)
}

/INFO sink Received/{
    print($10","$5","$8",0,0,NaN")
}

END {
}
