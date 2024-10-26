#pragma once

#include <string>
#include <vector>
#include <memory>
#include <atomic>
#include <mutex>

#include "CivetServer.h"
#include "civetweb.h"

namespace Communications
{
    // Fixme : 将这个新的链接的指针保存下来，然后我们就可以随时向他发送消息了

    struct SocketClient
    {
        mg_connection * conn;
        
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
        bool handleConnection(CivetServer *server, const struct mg_connection *conn) override;

        // 当 WebSocket 连接进入准备状态时触发（连接建立后）
        void handleReadyState(CivetServer *server, struct mg_connection *conn) override;

        // 当接收到 WebSocket 消息时触发
        bool handleData(CivetServer *server, struct mg_connection *conn, int bits, char *data, size_t data_len) override;

        // 当 WebSocket 连接关闭时触发
        void handleClose(CivetServer *server, const struct mg_connection *conn) override;


    private:
        std::vector<SocketClient> m_sockClient;
        std::mutex m_mtx;
    };

} // namespace Communications

