##Run the following docker Commands:

docker build -t ubuntu-python3.6-rocksdb-grpc:1.0 .

docker network create -d bridge --subnet 192.168.0.0/24 --gateway 192.168.0.1 dockernet

docker run -it --rm --name grpc-tools -v "$PWD":/usr/src/myapp -w /usr/src/myapp ubuntu-python3.6-rocksdb-grpc:1.0 python3.6 -m grpc.tools.protoc -I. --python_out=. --grpc_python_out=. replicator.proto

docker run -p 3000:3000 -it --rm --name assignment2master -v "$PWD":/usr/src/myapp -w /usr/src/myapp ubuntu-python3.6-rocksdb-grpc:1.0 python3.6 master.py

docker run -it --rm --name assignment2-slave -v "$PWD":/usr/src/myapp -w /usr/src/myapp ubuntu-python3.6-rocksdb-grpc:1.0 python3.6 slave.py 192.168.0.1

docker run -it --rm --name assignment2-test -v "$PWD":/usr/src/myapp -w /usr/src/myapp ubuntu-python3.6-rocksdb-grpc:1.0 python3.6 TestClient.py 192.168.0.1
