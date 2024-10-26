#include "WebSocketHandler.h"

#include "json.hpp"
#include "Logger.hpp"

using json = nlohmann::json;
using namespace Common;

namespace Communications
{
    bool WebSocketHandler::handleConnection(CivetServer *server, const struct mg_connection *conn)  {
        Common::log("WebSocket connected");
        return true;  // 返回 true 表示接受连接
    }

    // 当 WebSocket 连接进入准备状态时触发（连接建立后）
    void WebSocketHandler::handleReadyState(CivetServer *server, struct mg_connection *conn)  {
        std::string message = "Hello from server!";
        mg_websocket_write(conn, MG_WEBSOCKET_OPCODE_TEXT, message.c_str(), message.size());
        m_sockClient.emplace_back(conn);
        Common::log("Sent message: %s", message.c_str());
    }

    // 当接收到 WebSocket 消息时触发
    bool WebSocketHandler::handleData(CivetServer *server, struct mg_connection *conn, int bits, char *data, size_t data_len)  {
        std::string received(data, data_len);
        Common::log("Received message: %s", received.c_str());

        // 回复客户端的消息
        std::string reply = "Message received: " + received;
        mg_websocket_write(conn, MG_WEBSOCKET_OPCODE_TEXT, reply.c_str(), reply.size());

        return true;
    }

    // 当 WebSocket 连接关闭时触发
    void WebSocketHandler::handleClose(CivetServer *server, const struct mg_connection *conn)  {
        std::unique_lock<std::mutex> locker(m_mtx);
        Common::log("WebSocket closed");
    }
} // namespace Communications
