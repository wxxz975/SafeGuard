#include "HttpRequest.h"


namespace Communications
{
    std::string HttpRequest::getHeader(const std::string &key)
    {
        std::string value;
        const auto& iter = m_headers.find(key);
        if(iter != m_headers.end()) {
            value = iter->second;
        }
        
        return value;
    }

    void HttpRequest::addHeader(const std::string &key, const std::string &value)
    {
        m_headers[key] = value;
    }

    void HttpRequest::setMethod(const std::string& method) { 
        if(method == "GET") {
            m_method = Method::kGet;
        }else if(method == "POST") {
            m_method = Method::kPost;
        }else {
            m_method = Method::kInvalid;
        }
    };

} // namespace Communications
