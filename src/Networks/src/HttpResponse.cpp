#include "Networks/HttpResponse.h"

namespace Networks
{
    
    HttpResponse& HttpResponse::SetStatusCode(HttpStatusCode code)
    {
        m_statusCode = code;
        return *this;
    }

    HttpResponse& HttpResponse::SetStatusMessage(const std::string &msg)
    {
        m_statusMsg = msg;
        return *this;
    }

    HttpResponse& HttpResponse::AddHeader(const std::string& key, const std::string& value)
    { 
        m_headers[key] = value; 
        return *this;
    }

    HttpResponse& HttpResponse::SetBody(const std::string& body)
    { 
        m_body = body;
        return *this; 
    }

    HttpResponse& HttpResponse::CloseConnection(bool isClose)
    {
        m_closeConnection = isClose;
        return *this;
    }

    HttpResponse& HttpResponse::SetContentType(const std::string &type)
    {
        AddHeader("Content-Type", type);
        return *this;
    }

    void HttpResponse::SetSimpleResponse(HttpStatusCode statusCode, const std::string &statusMsg, 
        const std::string &body, bool isClose, const std::string& contentType)
    {
        SetStatusCode(statusCode);
        SetStatusMessage(statusMsg);
        CloseConnection(isClose);
        SetContentType(contentType);
        SetBody(body);
    }

    void HttpResponse::SetErrorResponse(const std::string& body)
    {
        SetSimpleResponse(HttpResponse::k400_BadRequest, "ERROR", body, true);
    }

    void HttpResponse::SetUnknownErrorResponse(const std::string &body)
    {
        SetSimpleResponse(HttpResponse::kUnknown, "UNKNOWN", body, true);
    }

    void HttpResponse::SetOkResponse(const std::string &body)
    {
        SetSimpleResponse(HttpResponse::k200_Ok, "Ok", body, false);
    }

    void HttpResponse::SetJsonResponse(const std::string &json)
    {
        SetStatusCode(HttpResponse::k200_Ok);
        AddHeader("Access-Control-Allow-Origin", "*");
        AddHeader("Content-Type", "application/json");
        SetBody(json);
    }

    void HttpResponse::SetFileResponse(const std::string &filepath)
    {
        m_filepath = filepath;
        m_sendfile = true;
    }
} // namespace Networks


