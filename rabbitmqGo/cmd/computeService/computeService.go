package main

import (
	"flag"
	"log"
	"sync"
	"time"

	/* for rmq access */
	"github.com/streadway/amqp"
)

/*
* training to learn go (same idea as safecounter in gotour but made on my own)
 */
type safecounter struct {
	l   sync.Mutex
	val int
}

func (counter *safecounter) incr() {
	counter.l.Lock()
	counter.val++
	counter.l.Unlock()
}

func (counter *safecounter) dec() {
	counter.l.Lock()
	counter.val--
	counter.l.Unlock()
}
func (counter *safecounter) getVal() int {
	counter.l.Lock()
	defer counter.l.Unlock()
	return counter.val
}

func failOnError(err error, msg string) {
	if err != nil {
		log.Fatalf("%s: %s", msg, err)
	}
}

func main() {
	// CLI flags
	rmqHost := flag.String("r", "amqp://guest:guest@localhost:5672/", "RabbitMQ host")
	inputMB := flag.String("i", "service1", "Input Mailbox")
	outputMB := flag.String("o", "serviceOut", "Output Mailbox")
	serviceName := flag.String("n", "computeService1", "Service name")
	computationCost := flag.Int("c", 100000, "Computation cost (iteration amount)")

	flag.Parse()
	/* END CLI flags*/

	conn, err := amqp.Dial(*rmqHost)
	failOnError(err, "Failed to connect to RabbitMQ")
	defer conn.Close()

	ch, err := conn.Channel()
	failOnError(err, "Failed to open a channel")
	defer ch.Close()

	q, err := ch.QueueDeclare(
		*inputMB, // name
		false,    // durable
		false,    // delete when unused
		false,    // exclusive
		false,    // no-wait
		nil,      // arguments
	)
	failOnError(err, "Failed to declare a queue")

	qo, err := ch.QueueDeclare(
		*outputMB, // name
		false,     // durable
		false,     // delete when unused
		false,     // exclusive
		false,     // no-wait
		nil,       // arguments
	)
	failOnError(err, "Failed to declare a queue")

	msgs, err := ch.Consume(
		q.Name, // queue
		"",     // consumer
		true,   // auto-ack
		false,  // exclusive
		false,  // no-local
		false,  // no-wait
		nil,    // args
	)
	failOnError(err, "Failed to register a consumer")

	forever := make(chan bool)

	// counter for parallelisation degree measurement
	counterPar := safecounter{val: 0}
	counterTotRec := safecounter{val: 0}

	sendToNextServ := make(chan int)
	go func() {
		for range /*d :=*/ msgs {
			beginTime := time.Now()
			counterTotRec.incr()

			go func(beg time.Time) {
				//log.Println("Start execution of request")
				startLoopTime := time.Now()
				go counterPar.incr()
				for i := 0; i < *computationCost; i++ {
					/* Do Nothing */
				}
				endLoopTime := time.Now()
				// format: serviceName nbIter timestamp totDurInServ computeDur parExec totReqProcessed
				log.Println("EndReqLog", *serviceName, *computationCost, time.Now().UnixNano(),
					time.Now().Sub(beginTime).Nanoseconds(), endLoopTime.Sub(startLoopTime).Nanoseconds(),
					counterPar.getVal(), "a", counterTotRec.getVal())
				// one less once parallel process once we finished the loop
				go counterPar.dec()
				sendToNextServ <- 1
			}(beginTime)

		}
	}()

	go func() {
		body := "a"
		for range sendToNextServ {
			err = ch.Publish(
				"",      // exchange
				qo.Name, // routing key
				false,   // mandatory
				false,   // immediate
				amqp.Publishing{
					ContentType: "text/plain",
					Body:        []byte(body),
				})
		}
	}()
	log.Printf(" [*] Waiting for messages. To exit press CTRL+C")
	<-forever
	close(sendToNextServ)
}
