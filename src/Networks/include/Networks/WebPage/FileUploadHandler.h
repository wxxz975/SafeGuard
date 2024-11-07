#pragma once

#include <fstream>
#include <string>
#include <memory>
#include <functional>

#include "Networks/WebPageHandler.h"
#include "Networks/FileUploadFilter.h"

namespace Networks
{
    class HttpResponse;
    class FileUploadHandler: public WebPageHandler
    {
    public:
        typedef std::function<void(const std::string& filename, const std::string& storeDir)> ReceivedFileCallback;
        
        
        FileUploadHandler();
        ~FileUploadHandler();

        bool Initialize(void* user_data) override;


        void SetReceivedFileDir(const std::string& path);
        void SetReceivedFileCallback(const ReceivedFileCallback& callbak);
    private:
        bool HandlePostImpl(HttpResponse* resp, struct mg_connection *conn) override;

        bool IsUploadRequest(struct mg_connection* conn);

    private:
        enum class ReceiveStatus {
            Received,
            Reject,
            NotPermissionToWrite
        };
        
        struct FileUploadContext
        {
            std::string filename;
            std::string storeDir;
            std::shared_ptr<FileUploadFilter> filter;
            ReceiveStatus status = ReceiveStatus::Reject;
            
            FileUploadContext(std::shared_ptr<FileUploadFilter> filter, const std::string& store_dir = "", const std::string& filename = ""): 
                storeDir(store_dir), filename(filename), filter(filter)
                { }

            ~FileUploadContext()
            {
               
            }
        };

    private:

        static int field_found_callback(const char *key, const char *filename, char *path, size_t pathlen, void *user_data);
        static int field_get_callback(const char *key, const char *value, size_t valuelen, void *user_data);
        static int field_store_callback(const char *path, long long file_size, void *user_data);

    private:
        std::shared_ptr<FileUploadFilter> m_filter;
        ReceivedFileCallback m_receivedCallback;
        std::string m_storeDir;
    };
    
    
    
    
} // namespace Networks
