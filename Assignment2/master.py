import time
import grpc
import replicator_pb2
import replicator_pb2_grpc
import rocksdb
import queue
import uuid

from concurrent import futures

_ONE_DAY_IN_SECONDS = 60 * 60 * 24


class MyReplicatorServicer(replicator_pb2.ReplicatorServicer):

    def __init__(self):

        self.db = rocksdb.DB("master.db", rocksdb.Options(create_if_missing=True))
        self.replicator_queue = queue.Queue()

    def put_decorator(func):
        def wrapper(self, request, context):
            resp = replicator_pb2.Response(
                operation="put",
                key= request.key,
                data=request.data
            )
            self.replicator_queue.put(resp)
            return func(self, request, context)

        return wrapper

    def delete_decorator(func):
        def wrapper(self, request, context):
            resp = replicator_pb2.Response(
                operation="delete",
                key=request.key,
                data=""
            )
            self.replicator_queue.put(resp)
            return func(self, request, context)

        return wrapper

    @put_decorator
    def put(self, request, context):
        print("Put operation in assignment2_master "+ request.key + " " + request.data)
        self.db.put(request.key.encode(), request.data.encode())
        return replicator_pb2.GetRequest()

    @delete_decorator
    def delete(self, request, context):
        print("Delete operation in assignment2_master "+ request.key )
        self.db.delete(request.key.encode())
        return replicator_pb2.GetRequest()

    def synchronizer(self, request, context):

        print(" Syncronization between server and client")

        itKey = self.db.iterkeys()
        itKey.seek_to_first()
        lKey = list(itKey)

        for key in lKey:
            data = self.db.get(key)
            response = replicator_pb2.Response(operation="put", key=key.decode(), data=data.decode())
            print("Put Operation "+ key.decode() + " " + data.decode())

            yield response

        while(True):
            response = self.replicator_queue.get()
            if(response.operation == "put"):
               print("Operation " + response.operation + " " + response.key + " " + response.data)
            elif(response.operation == "delete"):
                 print("Operation " + response.operation + " " + response.key )

            yield response

def run(host, port):
    '''
    Run the GRPC server
    '''
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=2))
    replicator_pb2_grpc.add_ReplicatorServicer_to_server(MyReplicatorServicer(), server)
    server.add_insecure_port('%s:%d' % (host, port))
    server.start()

    try:
        while True:
            print("Server started at...%d" % port)
            time.sleep(_ONE_DAY_IN_SECONDS)
    except KeyboardInterrupt:
        server.stop(0)


if __name__ == '__main__':
    print("... here ...")
    run('0.0.0.0', 3000)
