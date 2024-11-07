#pragma once
#include <string>
#include <map>

namespace Networks
{
    class WebPageHandler;

    class HttpResponse
    {
    public:
        friend class WebPageHandler;
        
        enum HttpStatusCode
        {
            kUnknown,
            k200_Ok = 200,
            k301_MovedPermanently = 301,
            k400_BadRequest = 400,
            k404_NotFound = 404,
        };

        HttpResponse() = default;
        ~HttpResponse() = default;

        HttpResponse& SetStatusCode(HttpStatusCode code);
        HttpResponse& SetStatusMessage(const std::string& msg);
        HttpResponse& AddHeader(const std::string& key, const std::string& value);
        HttpResponse& SetBody(const std::string& body);
        HttpResponse& CloseConnection(bool isClose);
        HttpResponse& SetContentType(const std::string& type);


        void SetSimpleResponse(HttpStatusCode statusCode, const std::string& statusMsg, 
                const std::string& body, bool isClose, const std::string& contentType = "text/plain");
        void SetErrorResponse(const std::string& body);
        void SetUnknownErrorResponse(const std::string& body);

        void SetOkResponse(const std::string& body);

        void SetJsonResponse(const std::string& json);

        void SetFileResponse(const std::string& filepath);

    private:
        HttpStatusCode m_statusCode;
        std::string m_statusMsg;
        std::map<std::string, std::string> m_headers;
        std::string m_body;
        bool m_closeConnection;

        bool m_sendfile = false;
        std::string m_filepath;
    };

} // namespace Networks
