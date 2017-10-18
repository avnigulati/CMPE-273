from flask import Flask, request, jsonify
import uuid
import rocksdb
import subprocess

app = Flask(__name__)


@app.route('/api/v1/scripts', methods=["POST"])
def put_file():

    db = rocksdb.DB("assignment.db", rocksdb.Options(create_if_missing=True))
    file = request.files['data']
    key = uuid.uuid4().hex
    db.put(key.encode('utf-8'), file.read().encode('utf-8'))
    return jsonify({"script-id": key}), 201


@app.route("/api/v1/scripts/<script_id>", methods=['GET'])
def get_file(script_id):
    db = rocksdb.DB("assignment1.db", rocksdb.Options(create_if_missing=True))
    foo_id = db.get(script_id.encode('utf-8'))
    response = subprocess.check_output(["python3.6", "-c", foo_id])
    return response

if __name__ == '__main__':
    app.run(port=8000)




