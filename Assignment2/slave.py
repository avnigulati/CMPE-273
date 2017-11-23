import rocksdb;
import time;
import grpc
import replicator_pb2
import argparse

PORT = 3000

class Slave(object):
    def __init__(self, host='0.0.0.0', port=PORT):
        
        self.channel = grpc.insecure_channel('%s:%d' % (host, port))
        self.stub = replicator_pb2.ReplicatorStub(self.channel)
        self.db = rocksdb.DB("slave.db", rocksdb.Options(create_if_missing=True))
        self.sync()

    def sync(self):
        syncro = self.stub.synchronizer(replicator_pb2.Request(data="start"))

        for s in syncro:
            if s.operation == "put":
                print("Operation Performed : " + s.operation + " " + s.key + " " + s.data)
                self.db.put(s.key.encode(), s.data.encode())
            elif s.operation == "delete":
                print("Operation Performed : " + s.operation + " " + s.key)
                self.db.put(s.key.encode(), s.data.encode())


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("host", help="the ip of the server")
    args = parser.parse_args()
    print("Slave is connecting to Master at {}:{}...".format(args.host, PORT))
    slave = Slave(host=args.host)


if __name__ == "__main__":
    main()
