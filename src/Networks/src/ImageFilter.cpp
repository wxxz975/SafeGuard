#include "Networks/ImageFilter.h"





namespace Networks
{
    const std::vector<std::string> ImageFilter::suffixes = {
        "jpg", "jpeg",
        "png",
        "gif",
        "bmp"
    };
    ImageFilter::ImageFilter()
    {
        m_filter = std::make_unique<SuffixFilter>(suffixes);
    }

    bool ImageFilter::IsValid(const std::string &filename)
    {
        return m_filter->IsValid(filename);
    }

} // namespace Networks


