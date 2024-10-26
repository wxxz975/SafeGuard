#pragma once
#include <string>
#include "SuffixFilter.h"



class FileFilter: public SuffixFilter
{
public:
    FileFilter(const std::vector<std::string>& suffixes);
    ~FileFilter() = default;
    
};
