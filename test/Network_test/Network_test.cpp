#include <unordered_map>
#include <string>
#include <chrono>
#include <thread>
#include "Common/IFilesystem.h"
#include "Networks/HttpServer.h"
#include "Networks/WebPage/FileUploadHandler.h"
#include "Networks/WebPage/MainWebPageHandler.h"
#include "Networks/WebPage/WebSocketHandler.h"

#include "Common/Logger.h"

int main(int argc, char* argv[])
{
    
    std::unordered_map<std::string, std::string> configs = {
        {"listening_ports", "8080"},
        {"document_root", "/home/wxxz/workspace/SafeGuard/frontends"}
    };
    Networks::HttpServer server = Networks::HttpServer();
    if(server.Initialize(configs)) {
        auto fileHandler = std::make_unique<Networks::FileUploadHandler>();
        fileHandler->SetReceivedFileDir(Common::IFilesystem::GetCurrentPath());
        auto mainHandler = std::make_unique<Networks::MainWebPageHandler>();
        auto sockHandler = std::make_unique<Networks::WebSocketHandler>();
        server.AddPageHandler("/upload", std::move(fileHandler));
        server.AddPageHandler("/main", std::move(mainHandler));
        server.AddSocketHandler("/ws", std::move(sockHandler));

        while(1) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            Common::logInfo("running!");
        }
    }

    return 0;
}