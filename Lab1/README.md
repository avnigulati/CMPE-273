# CMPE-273

Client console output:

Avnis-MBP:lab1 avni$ docker run -it --rm --name lab1-client -v "$PWD":/usr/src/myapp -w /usr/src/myapp ubuntu-python3.6-rocksdb-grpc:1.0 python3.6 client.py 192.168.0.1
Client is connecting to Server at 192.168.0.1:3000...
## PUT Request: value = foo
## PUT Response: key = c5603c6280d04175b1f47ba514bb5180
## GET Request: key = c5603c6280d04175b1f47ba514bb5180
## GET Response: value = foo
