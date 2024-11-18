#include "Networks/WebPage/WebSocketHandler.h"

#include "Common/json.hpp"
#include "Common/Logger.h"

using json = nlohmann::json;
using namespace Common;

namespace Networks
{
    bool WebSocketHandler::handleConnection(CivetServer *server, const struct mg_connection *conn)  {
        Common::logInfo("WebSocket connected");
        return true;  // 返回 true 表示接受连接
    }

    // 当 WebSocket 连接进入准备状态时触发（连接建立后）
    void WebSocketHandler::handleReadyState(CivetServer *server, struct mg_connection *conn)  {
        //std::string message = "Hello from server!";
        // mg_websocket_write(conn, MG_WEBSOCKET_OPCODE_TEXT, message.c_str(), message.size());
        
        //Common::logInfo("Sent message: {}", message);
        m_sockClients.emplace_back(conn);
        Common::logInfo("New Connected!");
    }

    // 当接收到 WebSocket 消息时触发
    bool WebSocketHandler::handleData(CivetServer *server, struct mg_connection *conn, int bits, char *data, size_t data_len)  {
        std::string received(data, data_len);
        Common::logInfo("Received message: {}", received);
        return true;
    }

    // 当 WebSocket 连接关闭时触发
    void WebSocketHandler::handleClose(CivetServer *server, const struct mg_connection *conn)  {
    
        Common::logInfo("WebSocket closed");
        std::remove_if(m_sockClients.begin(), m_sockClients.end(), [=](SocketClient client){
            return client.conn == conn;
        });
    }

    void WebSocketHandler::WriteData(const void *ptr, size_t size)
    {
        /*
            enum {
            MG_WEBSOCKET_OPCODE_CONTINUATION = 0x0,
            MG_WEBSOCKET_OPCODE_TEXT = 0x1,
            MG_WEBSOCKET_OPCODE_BINARY = 0x2,
            MG_WEBSOCKET_OPCODE_CONNECTION_CLOSE = 0x8,
            MG_WEBSOCKET_OPCODE_PING = 0x9,
            MG_WEBSOCKET_OPCODE_PONG = 0xa
        };
        */
        //std::lock_guard<std::mutex> lock(m_clientsMutex); // 加锁保护

        for(int idx = 0; idx < m_sockClients.size(); ++idx) {
            mg_websocket_write(m_sockClients[idx].conn, MG_WEBSOCKET_OPCODE_TEXT, reinterpret_cast<const char*>(ptr), size);
        }

        // for (auto client = m_sockClients.begin(); client != m_sockClients.end(); ) {
        //     if (size != mg_websocket_write((*client).conn,
        //                                 MG_WEBSOCKET_OPCODE_TEXT,
        //                                 reinterpret_cast<const char*>(ptr), size)) {
        //         client = m_sockClients.erase(client); // 删除并继续到下一个
        //     } else {
        //         ++client; // 写入成功，继续到下一个客户端
        //     }
        // }
    }

    void WebSocketHandler::WriteData(const std::string &value)
    {
        WriteData(value.data(), value.size());
    }
} // namespace Networks


