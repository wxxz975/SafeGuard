#include "Networks/Broadcaster.h"
#include "Common/Logger.h"

namespace Networks
{
    

    Broadcaster::Broadcaster(short port) {

    #ifdef _WIN32
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
    #endif

        m_socket = socket(AF_INET, SOCK_DGRAM, 0);
        if (m_socket < 0) {
            Common::logError("Socket creation failed");;
            exit(EXIT_FAILURE);
        }

        int broadcastEnable = 1;
        if (setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST, (char*)&broadcastEnable, sizeof(broadcastEnable)) < 0) {
            Common::logError("Error in setting Broadcast option");
            exit(EXIT_FAILURE);
        }

        memset(&m_broadcastAddr, 0, sizeof(m_broadcastAddr));
        m_broadcastAddr.sin_family = AF_INET;
        m_broadcastAddr.sin_port = htons(port);
        m_broadcastAddr.sin_addr.s_addr = INADDR_BROADCAST;
    }

    Broadcaster::~Broadcaster() {
        if (m_broadcastThread.joinable()) {
            m_broadcastThread.join();
        }
    #ifdef _WIN32
        closesocket(m_socket);
        WSACleanup();
    #else
        close(m_socket);
    #endif

        if(m_serverInfo) {
            delete m_serverInfo;
            m_serverInfo = nullptr;
        }
    }

    void Broadcaster::Initialize(uint16_t port, const char* remotePath, const char* message) {
        m_serverInfo = new ServerInfo();
        std::strcpy(m_serverInfo->message, message);
        m_serverInfo->port = port;
        std::strcpy(m_serverInfo->remotePath, remotePath);

        m_broadcastThread = std::thread(&Broadcaster::BroadcastLoop, this);
    }

    void Broadcaster::BroadcastLoop() {
        while (true) {
            int sentBytes = sendto(m_socket, 
                    reinterpret_cast<void*>(m_serverInfo), sizeof(ServerInfo), 0,
                                (struct sockaddr*)&m_broadcastAddr, sizeof(sockaddr_in));
            if (sentBytes < 0) {
                Common::logError("Broadcast failed");
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } 
} // namespace Networks
