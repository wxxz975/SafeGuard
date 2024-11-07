#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include "Networks/WebPageHandler.h"
#include "civetweb/CivetServer.h"

namespace Networks
{
    class HttpServer final
    {
    public:
    typedef std::unordered_map<std::string, std::string> Config;

    public:
        HttpServer() = default;
        ~HttpServer();
        
        bool Initialize(const Config& configs);

        void AddPageHandler(const std::string& uri, std::unique_ptr<WebPageHandler> handler);

        void AddSocketHandler(const std::string& uri, std::unique_ptr<CivetWebSocketHandler> handler);

        //void SetReceivedFileDir(const std::string& path);
        
    private:

        std::unordered_map<std::string, std::unique_ptr<WebPageHandler>> m_webpages;
        std::unordered_map<std::string, std::unique_ptr<CivetWebSocketHandler>> m_socks;

        std::unique_ptr<CivetServer> m_civet_srv;
    };
    
    
    

    
} // namespace Networks


