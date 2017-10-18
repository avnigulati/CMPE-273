# Requirements

You will be implementing a dynamic Python invoker REST service. The service will have the following features:

## 1. Python Script Uploader

```bash
POST http://localhost:8000/api/v1/scripts
```

### Request


__foo.py__

```python
# foo.py
print("Hello World")
```

```bash
curl -i -X POST -H "Content-Type: multipart/form-data" 
-F "data=@/tmp/foo.py" http://localhost:8000/api/v1/scripts
```

```bash
201 Created
```

```json
{
    "script-id": "123456"
}
```

## 2. Python Script Invoker

```bash
GET http://localhost:8000/api/v1/scripts/{script-id}
```

### Request

```bash
curl -i
http://localhost:8000/api/v1/scripts/123456
```

```bash
200 OK
```

```json
Hello World
```



