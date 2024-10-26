#include "SuffixFilter.h"
#include <sstream>
#include "Logger.hpp"

SuffixFilter::SuffixFilter(const std::vector<std::string> &suffixes)
{
    std::ostringstream oss;
    oss << ".*\\.(";
    for(int idx = 0; idx < suffixes.size(); ++idx) {
        oss << suffixes[idx];
        if(idx < suffixes.size() - 1) {
            oss << "|";
        }
    }
    oss << ")$";

    m_regex = std::regex(oss.str());
}

bool SuffixFilter::isValid(const std::string &path) const
{
    return std::regex_match(path, m_regex);
}
   
   
