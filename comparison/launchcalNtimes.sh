for i in `seq $1 1 $2`
do
	docker run -d -v ~/log_dock:/logs --cpus 1 --network host --rm -ti expe/rmqexpe:latest /bin/bash -c "cd /expeFiles && logDir=/logs suffix=exp${i} N1COST=1100000 bash launchOnce.sh"
done
