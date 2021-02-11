
HOST_CALV="localhost"
# specify a pre/suf/fix to the logfiles
[ -z "${prefix}" ] && prefix=""
[ -z "${suffix}" ] && suffix=""

if  [[ $1 = "up" ]]
then
    echo "-----------------------"
    echo "Deploy runtimes"
    echo "-----------------------"

    # trigger and constant runtime
    CALVIN_GLOBAL_STORAGE_TYPE=\"local\" csruntime --host ${HOST_CALV} --port 5000 --controlport 5001 --name runtime-0 -f ${prefix}_runtimelog0_${suffix} &

    # sink and spansink
    CALVIN_GLOBAL_STORAGE_TYPE=\"local\" csruntime --host ${HOST_CALV} --port 5002 --controlport 5003 --name runtime-1 -f ${prefix}_runtimelog1_${suffix} &

    # dummyTask1
    CALVIN_GLOBAL_STORAGE_TYPE=\"local\" csruntime --host ${HOST_CALV} --port 5004 --controlport 5005 --name runtime-2 -f ${prefix}_runtimelog2_${suffix} &

    # dummyTask2
    CALVIN_GLOBAL_STORAGE_TYPE=\"local\" csruntime --host ${HOST_CALV} --port 5006 --controlport 5007 --name runtime-3 -f ${prefix}_runtimelog3_${suffix} &

    # dummyTask3
    CALVIN_GLOBAL_STORAGE_TYPE=\"local\" csruntime --host ${HOST_CALV} --port 5008 --controlport 5009 --name runtime-4 -f ${prefix}_runtimelog4_${suffix} &
    echo "Deployment done"
elif [[ $1 = "app" ]]
then
    echo "-----------------------"
    echo "Deploy app ${2}"
    echo "-----------------------"
    cscontrol http://${HOST_CALV}:5001 deploy --reqs app.deployjson $2
elif [[ $1 = "down" ]]
then
    echo "-----------------------"
    echo "Delete runtimes"
    echo "-----------------------"
    pkill -9 csruntime
elif [[ $1 = "listapps" ]]
then
    echo "-----------------------"
    echo "Running applications"
    echo "-----------------------"
    cscontrol http://${HOST_CALV}:5001 applications list

else
    echo "up: deploy runtimes"
    echo "down: remove runtimes"
    echo "app <file.calvin>: deploy the application (runtimes must be started)"
fi
