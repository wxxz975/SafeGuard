#pragma once
#include <cstring>
#include <string>
#include <cstdint>
#include <thread>

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

namespace Networks
{
    
    struct ServerInfo {
        char message[32];
        uint16_t port;
        char ipAddress[16];
        char remotePath[64];
    };


    class Broadcaster {
    public:
        Broadcaster(short port = 7896);
        ~Broadcaster();
        void Initialize(uint16_t port, const char* remotePath, const char* message = "SafeGuard_Monitor");

    private:
        void BroadcastLoop();

        int m_socket;
        sockaddr_in m_broadcastAddr;
        ServerInfo* m_serverInfo;
        std::thread m_broadcastThread;
    }; 
};
