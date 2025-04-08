import asyncio
import websockets
import logging
import json
from datetime import datetime, timezone

logging.basicConfig(level=logging.INFO)

connected_clients = set()

def get_current_utc_time():
    return datetime.now(timezone.utc).isoformat()

async def handle_connection(websocket, path):
    logging.info(f"Novo cliente conectado: {path}")
    connected_clients.add(websocket)
    try:
        async for message in websocket:
            logging.info(f"Recebido: {message}")
            data = json.loads(message)
            action = data[2]
            if action == "BootNotification":
                response = [data[1], {
                    "status": "Accepted",
                    "currentTime": get_current_utc_time(),
                    "interval": 10
                }]
            elif action == "Heartbeat":
                response = [data[1], {
                    "currentTime": get_current_utc_time()
                }]
            elif action == "StartTransaction":
                response = [data[1], {"transactionId": 123}]
            elif action == "StopTransaction":
                response = [data[1], {}]
            elif action == "MeterValues":
                response = [data[1], {}]
            else:
                response = [data[1], {"error": "UnknownAction"}]
            await websocket.send(json.dumps(response))
    finally:
        connected_clients.remove(websocket)

start_server = websockets.serve(handle_connection, "localhost", 9000)
logging.info("Servidor WebSocket iniciado na porta 9000")

asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()
