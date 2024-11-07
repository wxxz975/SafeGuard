#pragma once
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

#include "Inference/Base/BoundingBox.h"

namespace Networks
{
    class ResponseJsonBuilder
    {
    public:        

        ResponseJsonBuilder() = default;
        ~ResponseJsonBuilder() = default;

        static std::string CreateHisoryQueryResponse(bool status, const std::string& msg = "", const std::map<std::string, int>& statistic = std::map<std::string, int>());
        
        static std::string CreateNewResultMessage(const std::string& filename, 
            const std::vector<Inference::Base::BoundingBox>& boxes, const std::vector<std::string>& labels);


        static std::string CreateInitResponse(const std::vector<std::string>& modelLists, 
                const std::vector<std::string>& frameworkLists, 
                const std::vector<std::string>& algorithmLists,
                int curModelIdx, int curFrameworkIdx, int curAlgoIdx);

        static std::string CreateModelSwitchResponse(
                bool status,
                const std::string& modelName, 
                const std::string& algo, 
                const std::string& framework,
                const std::vector<std::string>& labels);

        static std::string CreateSettingsUpdateResponse(bool status, 
            const std::unordered_map<std::string, std::string>& values = std::unordered_map<std::string, std::string>());
    };
} // namespace Networks

