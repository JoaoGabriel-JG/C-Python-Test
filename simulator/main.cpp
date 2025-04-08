#include <ixwebsocket/IXWebSocket.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std::chrono_literals;

int main() {
    ix::WebSocket ws;
    ws.setUrl("ws://localhost:9000");

    ws.setOnMessageCallback([](const ix::WebSocketMessagePtr& msg) {
        if (msg->type == ix::WebSocketMessageType::Message) {
            std::cout << "Recebido do servidor: " << msg->str << std::endl;
        }
    });

    ws.start();
    std::this_thread::sleep_for(1s); // espera conexão

    // Envia BootNotification
    json boot = json::array({2, "123", "BootNotification", {
        {"chargePointModel", "Model X"},
        {"chargePointVendor", "OpenAI Charger"}
    }});
    ws.send(boot.dump());
    std::this_thread::sleep_for(1s);

    // Envia Heartbeat
    json heartbeat = json::array({2, "124", "Heartbeat", {}});
    ws.send(heartbeat.dump());
    std::this_thread::sleep_for(1s);

    // StartTransaction
    json startTx = json::array({2, "125", "StartTransaction", {
        {"connectorId", 1},
        {"idTag", "ABC123"},
        {"meterStart", 0},
        {"timestamp", "2025-04-07T12:00:00Z"}
    }});
    ws.send(startTx.dump());
    std::this_thread::sleep_for(1s);

    // MeterValues
    json meter = json::array({2, "126", "MeterValues", {
        {"connectorId", 1},
        {"transactionId", 123},
        {"meterValue", {{
            {"timestamp", "2025-04-07T12:01:00Z"},
            {"sampledValue", {{
                {"value", "1000"}
            }}}
        }}}
    }});
    ws.send(meter.dump());
    std::this_thread::sleep_for(1s);

    // StopTransaction
    json stopTx = json::array({2, "127", "StopTransaction", {
        {"transactionId", 123},
        {"meterStop", 2000},
        {"timestamp", "2025-04-07T12:05:00Z"},
        {"idTag", "ABC123"}
    }});
    ws.send(stopTx.dump());

    std::this_thread::sleep_for(3s);
    ws.stop();

    return 0;
}
