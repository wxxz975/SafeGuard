#include "FileUploadFilter.h"

#include "ImageFilter.h"

namespace Communications
{
    FileUploadFilter::FileUploadFilter()
    {
        m_filter = std::make_unique<ImageFilter>();
    }

    bool FileUploadFilter::isValid(const std::string &filename)
    {
        return m_filter->isValid(filename);
    }
    
} // namespace Communications

