#pragma once

#include <string>
#include <vector>
#include <memory>

namespace Networks
{
    class FileUploadFilter
    {
    public:
        FileUploadFilter() = default;
        ~FileUploadFilter() = default;

        virtual bool IsValid(const std::string& filename) = 0;
    };
    
    
    
} // namespace Networks
