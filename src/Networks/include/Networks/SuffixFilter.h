#pragma once
#include <regex>
#include <string>

class SuffixFilter
{
public:
    SuffixFilter(const std::vector<std::string>& suffixes);
    ~SuffixFilter() = default;

    bool isValid(const std::string& path) const;


private:

    std::regex m_regex;
};

