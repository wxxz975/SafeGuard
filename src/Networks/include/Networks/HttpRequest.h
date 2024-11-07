#pragma once
#include <map>
#include <string>

namespace Networks
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
        
        
        std::string GetHeader(const std::string& key) const;
        void AddHeader(const std::string& key, const std::string& value);
        Method GetMethod() const { return m_method; } ;
        void SetMethod(const std::string& method);
        void SetMethod(Method method) { m_method = method; };
        std::string GetPath() const { return m_path; };
        void SetPath(const std::string& path) { m_path = path; };


    private:
        Method m_method;
        std::string m_path;
        std::map<std::string, std::string> m_headers;
    };


} // namespace Networks
