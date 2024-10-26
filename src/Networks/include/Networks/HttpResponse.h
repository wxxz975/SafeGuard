#pragma once
#include <string>
#include <map>

namespace Communications
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

        HttpResponse& setStatusCode(HttpStatusCode code);
        HttpResponse& setStatusMessage(const std::string& msg);
        HttpResponse& addHeader(const std::string& key, const std::string& value);
        HttpResponse& setBody(const std::string& body);
        HttpResponse& closeConnection(bool isClose);
        HttpResponse& setContentType(const std::string& type);


        void setSimpleResponse(HttpStatusCode statusCode, const std::string& statusMsg, 
                const std::string& body, bool isClose, const std::string& contentType = "text/plain");
        void setErrorResponse(const std::string& body);
        void setUnknownErrorResponse(const std::string& body);

        void setOkResponse(const std::string& body);

        void setJsonResponse(const std::string& json);

    private:
        HttpStatusCode m_statusCode;
        std::string m_statusMsg;
        std::map<std::string, std::string> m_headers;
        std::string m_body;
        bool m_closeConnection;
    };

} // namespace Communications
