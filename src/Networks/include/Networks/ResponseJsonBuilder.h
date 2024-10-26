#pragma once
#include <string>
#include <vector>
#include <map>

#include "json.hpp"


struct BoundingBox
{
    std::int32_t    left;
    std::int32_t    top;
    std::int32_t    width;
    std::int32_t    height;
    float           confidence;
    std::size_t     class_index;

    BoundingBox():left(0), top(0), width(0), height(0), confidence(0), class_index(0){};
    BoundingBox(std::int32_t left, std::int32_t top, 
            std::int32_t width, std::int32_t height, 
            float confidence, std::size_t class_index):
                left(left), top(top), width(width), height(height),
                confidence(confidence), class_index(class_index)
    {

    };
};

class ResponseJsonBuilder
{
public:
    using json = nlohmann::json;

    ResponseJsonBuilder() = default;
    ~ResponseJsonBuilder() = default;


    
    static std::string buildNewImageResponse(const std::string& filename, 
        const std::vector<BoundingBox>& boxes, const std::vector<std::string>& labels);


    [[deprecated("This function is deprecated")]]
    static std::string buildInitResponse(const std::vector<std::string>& modelLists = std::vector<std::string>());


    static std::string buildLoadingModelResponse(const std::string& modelName, 
            const std::vector<std::string>& labels);
};

