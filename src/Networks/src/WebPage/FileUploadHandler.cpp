#include "Networks/WebPage/FileUploadHandler.h"

#include "Networks/HttpResponse.h"
#include "Networks/ImageFilter.h"

#include "Common/IFilesystem.h"
#include "Common/Logger.h"


namespace Networks
{
    //FileUploadFilter FileUploadHandler::m_filter;
    //FileUploadHandler::ReceivedFileCallback m_receivedCallback = nullptr;


    FileUploadHandler::FileUploadHandler()
        :m_filter(std::make_shared<ImageFilter>())
    {
    }

    FileUploadHandler::~FileUploadHandler()
    {

    }

    bool FileUploadHandler::Initialize(void *user_data)
    {
        return true;
    }
    
    void FileUploadHandler::SetReceivedFileDir(const std::string &path)
    {
        if(!Common::IFilesystem::IsExist(path)) Common::IFilesystem::CreateDir(path);
       
        m_storeDir = path;
    }

    void FileUploadHandler::SetReceivedFileCallback(const ReceivedFileCallback &callbak)
    {
        m_receivedCallback = callbak;
    }
    bool FileUploadHandler::HandlePostImpl(HttpResponse *resp, mg_connection *conn)
    {
        Common::logDebug("Post Request!");
        auto* info = mg_get_request_info(conn);
        
        if (IsUploadRequest(conn))
        {
            // 设置表单处理的回调
            mg_form_data_handler fdh;
            FileUploadContext context(m_filter, m_storeDir);
            fdh.field_found = field_found_callback; // 发现表单字段时调用
            fdh.field_get = field_get_callback;     // 接收到数据时调用
            fdh.field_store = field_store_callback; // 文件上传完成时调用
            fdh.user_data = &context;

            // 处理表单请求
            if(mg_handle_form_request(conn, &fdh) >= 0)
            {
                switch (context.status)
                {
                case ReceiveStatus::Received:
                {
                    resp->SetOkResponse("Upload success.");
                    Common::logInfo("Received File:{}", context.filename);
                    if(m_receivedCallback) m_receivedCallback(context.filename, context.storeDir);
                    break;
                }
                case ReceiveStatus::Reject: 
                {
                    resp->SetErrorResponse("Upload reject.");
                    Common::logInfo("Reject file:{}", context.filename);
                    break;
                }
                case ReceiveStatus::NotPermissionToWrite:
                {
                    resp->SetErrorResponse("Not Permission.");
                    Common::logInfo("Not Permission receive file:{}", context.filename);
                    break;
                }
                default:
                    resp->SetUnknownErrorResponse("Internal Error.");
                    Common::logError("Internal Error");
                }
            }     
            
            return true;
        }
        
        return true;
    }

    bool FileUploadHandler::IsUploadRequest(mg_connection *conn)
    {
        const struct mg_request_info *req_info = mg_get_request_info(conn);
        auto ct = mg_get_header(conn, "Content-Type");
        if(ct == nullptr) return false;
        std::string content_type =  ct;
        return !content_type.empty() && content_type.find("multipart/form-data") != std::string::npos;
    }

   
    int FileUploadHandler::field_found_callback(const char *key, const char *filename, char *path, size_t pathlen, void *user_data)
    {
        using namespace Common;
        FileUploadContext *context = reinterpret_cast<FileUploadContext *>(user_data);
        const auto& filter = context->filter;
        context->filename = IFilesystem::GetFilename(filename);
        
        if (filename && filter->IsValid(filename))
        {
            std::string save_path = IFilesystem::ConcatPath(context->storeDir, context->filename);
            snprintf(path, pathlen, "%s", save_path.c_str());
            return MG_FORM_FIELD_STORAGE_STORE; 
        }

        Common::logInfo("Reject file!");
        context->status = ReceiveStatus::Reject;
        return MG_FORM_FIELD_STORAGE_SKIP; 
    }

    int FileUploadHandler::field_get_callback(const char *key, const char *value, size_t valuelen, void *user_data)
    {
       
        return MG_FORM_FIELD_HANDLE_ABORT; // other error
    }

    int FileUploadHandler::field_store_callback(const char *path, long long file_size, void *user_data)
    {
        FileUploadContext *context = reinterpret_cast<FileUploadContext *>(user_data);
        // if(m_receivedCallback) {
        //     m_receivedCallback(context->filename, context->storeDir);
        // }
        context->status = ReceiveStatus::Received;
        
        return MG_FORM_FIELD_HANDLE_NEXT;
    }

} // namespace Networks


