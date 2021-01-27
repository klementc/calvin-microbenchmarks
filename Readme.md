# Dependency

jaegertracing-python to obtain traces, python2 for calvin (yes it would be better to use up to date python but we can't..), calvin:

```
virtualenv -p /usr/bin/python2 venv
source venv/bin/activate

pip install jaeger-client
pip install er-calvin 
```

