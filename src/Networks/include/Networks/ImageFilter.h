#pragma once
#include <string>
#include <vector>
#include <memory>

#include "Networks/FileUploadFilter.h"

#include "SuffixFilter.h"

namespace Networks
{
    class ImageFilter: public FileUploadFilter
    {
    public:
        ImageFilter();
        ~ImageFilter() = default;

        virtual bool IsValid(const std::string& filename) override;

    private:
        
        const static std::vector<std::string> suffixes;
        std::unique_ptr<SuffixFilter> m_filter;
    };

    
} // namespace Networks




