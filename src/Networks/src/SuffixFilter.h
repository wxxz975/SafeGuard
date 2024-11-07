#pragma once
#include <regex>
#include <string>


namespace Networks
{
    class SuffixFilter
    {
    public:
        SuffixFilter(const std::vector<std::string>& suffixes);
        ~SuffixFilter() = default;

        bool IsValid(const std::string& path) const;


    private:

        std::regex m_regex;
    };


} // namespace Networks



