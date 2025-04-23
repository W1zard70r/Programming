import json
import pprint

async def app(scope, receive, send):
    assert scope["type"] == "http"

    # print(scope)
    # pprint.pprint(scope)

    await receive()

    client_info = scope.get("client", ("unknown", "unknown"))
    ip_address, port = client_info[0], client_info[1]

    headers = dict(scope.get("headers", []))
    user_agent = headers.get(b"user-agent", b"").decode()

    data = {"ip": ip_address, "port": port, "browser": user_agent}

    await send(
        {
            "type": "http.response.start",
            "status": 200,
            "headers": [[b"content-type", b"application/json"]],
        }
    )
    
    await send(
        {
            "type": "http.response.body",
            "body": json.dumps(data).encode(),
        }
    )
