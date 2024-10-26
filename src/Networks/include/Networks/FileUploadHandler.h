#pragma once
#include "WebPageHandler.h"
#include <fstream>
#include <string>

#include "FileUploadFilter.h"

namespace Communications
{
    class HttpResponse;
    class FileUploadHandler: public WebPageHandler
    {
    public:
        FileUploadHandler();
        ~FileUploadHandler();

        bool Initialize(void* user_data) override;


        void setRecivedFileDir(const std::string& path);

    private:
        bool handlePostImpl(HttpResponse* resp, struct mg_connection *conn) override;

        bool isUploadRequest(struct mg_connection* conn);

    private:
        enum class ReceiveStatus {
            Received,
            Reject,
            NotPermissionToWrite
        };
        
        struct FileUploadContext
        {
            std::ofstream ofile;
            std::string filename;
            std::string storeDir;
            FileUploadFilter &filter;
            ReceiveStatus status = ReceiveStatus::Reject;
            
            FileUploadContext(FileUploadFilter& filter, const std::string& store_dir = "", const std::string& filename = ""): 
                storeDir(store_dir), filename(filename), filter(filter)
                { }

            ~FileUploadContext()
            {
                if(ofile.is_open()) ofile.close();
            }
        };

    private:

        static int field_found_callback(const char *key, const char *filename, char *path, size_t pathlen, void *user_data);
        static int field_get_callback(const char *key, const char *value, size_t valuelen, void *user_data);
        static int field_store_callback(const char *path, long long file_size, void *user_data);

    private:
        FileUploadFilter m_filter;

        std::string m_storeDir;
    };
    
    
    
    
} // namespace Communications
