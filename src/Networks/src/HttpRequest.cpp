#include "Networks/HttpRequest.h"


namespace Networks
{
    std::string HttpRequest:: GetHeader(const std::string &key) const
    {
        std::string value;
        const auto& iter = m_headers.find(key);
        if(iter != m_headers.end()) {
            value = iter->second;
        }
        
        return value;
    }

    void HttpRequest::AddHeader(const std::string &key, const std::string &value)
    {
        m_headers[key] = value;
    }

    void HttpRequest::SetMethod(const std::string& method) { 
        if(method == "Get") {
            m_method = Method::kGet;
        }else if(method == "POST") {
            m_method = Method::kPost;
        }else {
            m_method = Method::kInvalid;
        }
    };


    std::string HttpRequest::GetParams(const std::string& key) const
    {
        std::string result;
        if(m_params.count(key)) result = m_params.at(key);

        return result;
    }
    void HttpRequest::AddParams(const std::string& key, const std::string& value)
    {
        m_params[key] = value;
    }

} // namespace Networks
