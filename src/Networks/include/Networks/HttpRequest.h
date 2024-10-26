#pragma once
#include <map>
#include <string>

namespace Communications
{
    class HttpRequestParser;

    class HttpRequest
    {
    public:
        friend class HttpRequestParser;

        enum class Method
        {
            kInvalid, kGet, kPost, kHead, kPut, kDelete
        };

        HttpRequest() = default;
        ~HttpRequest() = default;
        
        
        std::string getHeader(const std::string& key);
        void addHeader(const std::string& key, const std::string& value);
        Method getMethod() { return m_method; };
        void setMethod(const std::string& method);
        void setMethod(Method method) { m_method = method; };
        std::string getPath() { return m_path; };
        void setPath(const std::string& path) { m_path = path; };


    private:
        Method m_method;
        std::string m_path;
        std::map<std::string, std::string> m_headers;
    };


} // namespace Communications
