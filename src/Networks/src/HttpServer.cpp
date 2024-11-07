#include "Networks/HttpServer.h"

#include <vector>

#include "Networks/WebPage/FileUploadHandler.h"
#include "Networks/WebPage/MainWebPageHandler.h"
#include "Networks/WebPage/WebSocketHandler.h"
#include "Common/Logger.h"

namespace Networks
{
    HttpServer::~HttpServer()
    {
        if(m_civet_srv) m_civet_srv->close();

    }

    bool HttpServer::Initialize(const Config &configs)
    {
        try
        {
            std::vector<std::string> civet_config;
            for(const auto& conf : configs) {
                civet_config.push_back(conf.first);
                civet_config.push_back(conf.second);
            }
            m_civet_srv = std::make_unique<CivetServer>(civet_config);
           
        }
        catch(const std::exception& e)
        {
            Common::logError("Failed to start http server! error:{}", e.what());
            return false;
        }

        return true;
    }
    void HttpServer::AddPageHandler(const std::string& uri,std::unique_ptr<WebPageHandler> handler)
    {
        m_civet_srv->addHandler(uri, handler.get());
        m_webpages.insert({uri, std::move(handler)});
    }
    void HttpServer::AddSocketHandler(const std::string& uri,std::unique_ptr<CivetWebSocketHandler> handler)
    {
        m_civet_srv->addWebSocketHandler(uri, handler.get());
        m_socks.insert({uri, std::move(handler)});
    }
   
} // namespace Networks
