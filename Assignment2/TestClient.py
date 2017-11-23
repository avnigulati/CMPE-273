import grpc
import replicator_pb2
import argparse

PORT = 3000

class TestClient():
    def __init__(self, host='0.0.0.0', port=PORT):
        self.channel = grpc.insecure_channel('%s:%d' % (host, port))
        self.stub = replicator_pb2.ReplicatorStub(self.channel)

    def put(self, key, value):
        return self.stub.put(replicator_pb2.PutOperation(key=key, data=value))

    def delete(self, key):
        return self.stub.delete(replicator_pb2.DeleteOperation(key=key))


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("host", help="the ip of the server")
    args = parser.parse_args()
    print("Client is connecting to Master at {}:{}...".format(args.host, PORT))
    test = TestClient(host=args.host)


    #Test 1

    print('Test put : key1, value1')
    output = test.put("key1","value1")
    
#    print(output.data)

    #Test 2
    print('Test put: key2, value2')
    output = test.put("key2","value2")
#    print(output.data)


    #Test 3
    print('Test delete: key1')
    output = test.delete("key1")
#    print('output.key')



if __name__ == "__main__":
    main()
