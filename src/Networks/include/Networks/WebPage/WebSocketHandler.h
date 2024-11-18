#pragma once

#include <string>
#include <vector>
#include <memory>
#include <atomic>
#include <mutex>

#include "civetweb/CivetServer.h"
#include "civetweb/civetweb.h"

namespace Networks
{
    // Fixme : 将这个新的链接的指针保存下来，然后我们就可以随时向他发送消息了

    struct SocketClient
    {
        mg_connection * conn;
        uint32_t idx = 0;
        
        SocketClient(mg_connection * conn)
            : conn(conn){

        }
    };

    // WebSocket 处理类
    class WebSocketHandler : public CivetWebSocketHandler {
    public:
        WebSocketHandler() = default;
        ~WebSocketHandler() = default;

        // 当有新的 WebSocket 连接时触发
        virtual bool handleConnection(CivetServer *server, const struct mg_connection *conn) override;

        // 当 WebSocket 连接进入准备状态时触发（连接建立后）
        virtual void handleReadyState(CivetServer *server, struct mg_connection *conn) override;

        // 当接收到 WebSocket 消息时触发
        virtual bool handleData(CivetServer *server, struct mg_connection *conn, int bits, char *data, size_t data_len) override;

        // 当 WebSocket 连接关闭时触发
        virtual void handleClose(CivetServer *server, const struct mg_connection *conn) override;

        void WriteData(const void* ptr, size_t size);

        void WriteData(const std::string& value);

    private:
        std::vector<SocketClient> m_sockClients;
        std::mutex m_clientsMutex;
    };

} // namespace Networks

