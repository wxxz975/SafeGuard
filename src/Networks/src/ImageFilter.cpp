#include "ImageFilter.h"


const std::vector<std::string> ImageFilter::suffixes = {
    "jpg", "jpeg",
    "png",
    "gif",
    "bmp"
};

ImageFilter::ImageFilter()
    : FileFilter(suffixes)
{
    
}