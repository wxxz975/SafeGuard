#include "HttpResponse.h"


namespace Communications
{
    
    HttpResponse& HttpResponse::setStatusCode(HttpStatusCode code)
    {
        m_statusCode = code;
        return *this;
    }

    HttpResponse& HttpResponse::setStatusMessage(const std::string &msg)
    {
        m_statusMsg = msg;
        return *this;
    }

    HttpResponse& HttpResponse::addHeader(const std::string& key, const std::string& value)
    { 
        m_headers[key] = value; 
        return *this;
    }

    HttpResponse& HttpResponse::setBody(const std::string& body)
    { 
        m_body = body;
        return *this; 
    }

    HttpResponse& HttpResponse::closeConnection(bool isClose)
    {
        m_closeConnection = isClose;
        return *this;
    }

    HttpResponse& HttpResponse::setContentType(const std::string &type)
    {
        addHeader("Content-Type", type);
        return *this;
    }

    void HttpResponse::setSimpleResponse(HttpStatusCode statusCode, const std::string &statusMsg, 
        const std::string &body, bool isClose, const std::string& contentType)
    {
        setStatusCode(statusCode);
        setStatusMessage(statusMsg);
        closeConnection(isClose);
        setContentType(contentType);
        setBody(body);
    }

    void HttpResponse::setErrorResponse(const std::string& body)
    {
        setSimpleResponse(HttpResponse::k400_BadRequest, "ERROR", body, true);
    }

    void HttpResponse::setUnknownErrorResponse(const std::string &body)
    {
        setSimpleResponse(HttpResponse::kUnknown, "UNKNOWN", body, true);
    }

    void HttpResponse::setOkResponse(const std::string &body)
    {
        setSimpleResponse(HttpResponse::k200_Ok, "Ok", body, false);
    }

    void HttpResponse::setJsonResponse(const std::string &json)
    {
        setStatusCode(HttpResponse::k200_Ok);
        addHeader("Access-Control-Allow-Origin", "*");
        addHeader("Content-Type", "application/json");
        setBody(json);
    }
} // namespace Communications
