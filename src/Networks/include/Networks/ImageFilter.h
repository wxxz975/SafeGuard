#pragma once
#include "FileFilter.h"
#include <string>
#include <vector>

class ImageFilter: public FileFilter
{
public:
    ImageFilter();
    ~ImageFilter() = default;
    
    const static std::vector<std::string> suffixes;
};

