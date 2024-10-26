#include "FileUploadHandler.h"


#include "HttpResponse.h"

#include "Filesystem.h"
#include "Logger.hpp"

namespace Communications
{
    //FileUploadFilter FileUploadHandler::m_filter;
    
    FileUploadHandler::FileUploadHandler()
    {

    }

    FileUploadHandler::~FileUploadHandler()
    {

    }

    bool FileUploadHandler::Initialize(void *user_data)
    {
        return true;
    }

    void FileUploadHandler::setRecivedFileDir(const std::string &path)
    {
        m_storeDir = path;
    }

    bool FileUploadHandler::handlePostImpl(HttpResponse *resp, mg_connection *conn)
    {
        if (isUploadRequest(conn))
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
                    resp->setOkResponse("Upload success.");
                    Common::log("Received File:%s\n", context.filename.c_str());
                    break;
                }
                case ReceiveStatus::Reject: 
                {
                    resp->setErrorResponse("Upload reject.");
                    Common::log("Reject file:%s\n", context.filename.c_str());
                    break;
                }
                case ReceiveStatus::NotPermissionToWrite:
                {
                    resp->setErrorResponse("Not Permission.");
                    Common::log("Not Permission receive file:%s\n", context.filename.c_str());
                    break;
                }
                default:
                    resp->setUnknownErrorResponse("Internal Error.");
                    Common::log("Internal Error");
                }
            }     
            
            return true;
        }
        

        
           
        return true;
    }

    bool FileUploadHandler::isUploadRequest(mg_connection *conn)
    {
        const struct mg_request_info *req_info = mg_get_request_info(conn);
        std::string content_type = mg_get_header(conn, "Content-Type");
        return !content_type.empty() && content_type.find("multipart/form-data") != std::string::npos;
    }

   
    int FileUploadHandler::field_found_callback(const char *key, const char *filename, char *path, size_t pathlen, void *user_data)
    {
        FileUploadContext *context = reinterpret_cast<FileUploadContext *>(user_data);
        auto& filter = context->filter;
        context->filename = IFilesystem::GetFilename(filename);
        if (filename && filter.isValid(filename))
        {
            std::string save_path = IFilesystem::ConcatPath(context->storeDir, context->filename);
            context->ofile.open(save_path, std::ios::binary | std::ios::out);
            
            if (!context->ofile.is_open())  {
                IFilesystem::DeleteFile(save_path);
                context->status = ReceiveStatus::NotPermissionToWrite;
                return MG_FORM_FIELD_STORAGE_SKIP; // 打开文件失败, 多半是权限问题 
            }

            context->status = ReceiveStatus::Received;
            return MG_FORM_FIELD_STORAGE_GET; 
        }

        context->status = ReceiveStatus::Reject;
        return MG_FORM_FIELD_STORAGE_SKIP; 
    }

    // /* Return values for "field_get" and "field_store" */
    // enum {
    //     /* Only "field_get": If there is more data in this field, get the next
    //     * chunk. Otherwise: handle the next field. */
    //     MG_FORM_FIELD_HANDLE_GET = 0x1,
    //     /* Handle the next field */
    //     MG_FORM_FIELD_HANDLE_NEXT = 0x8,
    //     /* Stop parsing this request */
    //     MG_FORM_FIELD_HANDLE_ABORT = 0x10
    // };

    int FileUploadHandler::field_get_callback(const char *key, const char *value, size_t valuelen, void *user_data)
    {
        FileUploadContext *context = reinterpret_cast<FileUploadContext *>(user_data);
        if (context->ofile.is_open()) {
            context->ofile.write(value, valuelen); // 写入接收到的数据块
            return MG_FORM_FIELD_HANDLE_GET;
        }

        return MG_FORM_FIELD_HANDLE_ABORT; // other error
    }

    int FileUploadHandler::field_store_callback(const char *path, long long file_size, void *user_data)
    {
        return MG_FORM_FIELD_HANDLE_ABORT;
    }

} // namespace Communications


