#pragma once
#include <string>
#include <vector>
#include <memory>
#include "FileFilter.h"


namespace Communications
{
    class FileUploadFilter
    {
    public:
        FileUploadFilter();
        ~FileUploadFilter() = default;

        bool isValid(const std::string& filename);

    private:
        
        std::unique_ptr<FileFilter> m_filter;
    };
    
    
    
} // namespace Communications
