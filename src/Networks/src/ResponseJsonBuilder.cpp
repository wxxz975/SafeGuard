#include "Networks/ResponseJsonBuilder.h"

#include "Common/json.hpp"


namespace Networks
{
    using json = nlohmann::json;

    std::string ResponseJsonBuilder::CreateHisoryQueryResponse(bool status, const std::string& msg, const std::map<std::string, int>& statistic)
    {   
        json doc;
        doc["cmd"] = "HistoryQueryResponse";
        doc["status"] = status;
        
        doc["args"]["Message"] = msg;
        doc["args"]["Statistic"] = statistic;

        return doc.dump();
    }

    std::string ResponseJsonBuilder::CreateNewResultMessage(const std::string &filename, 
        const std::vector<Inference::Base::BoundingBox> &boxes, 
        const std::vector<std::string>& labels)
    {
        
        json doc;
        doc["cmd"] = "NewResultMessage";
        doc["args"]["filename"] = filename;
        
        auto& items = doc["args"]["DetectedItem"];
        for(int idx = 0; idx < boxes.size(); ++idx) {
            int label_idx = boxes[idx].class_index;
            std::array<int, 4> coord = {boxes[idx].left, boxes[idx].top, boxes[idx].width, boxes[idx].height};
            items[idx]["Label"] = labels[label_idx];
            items[idx]["Confidence"] = boxes[idx].confidence;
            items[idx]["Coordinate"] = coord;
        }
        
        if(!boxes.size()) items = std::vector<int>();
        
        return doc.dump();
    }
    std::string ResponseJsonBuilder::CreateInitResponse(const std::vector<std::string> &modelLists, 
        const std::vector<std::string> &frameworkLists, 
        const std::vector<std::string> &algorithmLists, 
        int curModelIdx, int curFrameworkIdx, int curAlgoIdx)
    {
        json doc;
        doc["cmd"] = "InitResponse";
        
        doc["args"]["ModelNames"] = modelLists;
        doc["args"]["Framworks"] = frameworkLists;
        doc["args"]["Algorithms"] = algorithmLists;
        doc["args"]["CurrentModelIndex"] = curModelIdx;
        doc["args"]["CurrentFrameworkIndex"] = curFrameworkIdx;
        doc["args"]["CurrentAlgorithmIndex"] = curAlgoIdx;

        return doc.dump();
    }
    
    std::string ResponseJsonBuilder::CreateModelSwitchResponse(
                bool status,
                const std::string& modelName, 
                const std::string& algo, const std::string& framework,
                const std::vector<std::string>& labels)
    {
        json doc;
        doc["cmd"] = "ModelSwitchResponse";
        doc["args"]["ModelName"] = modelName;
        doc["args"]["Framework"] = framework;
        doc["args"]["Algorithm"] = algo;


        doc["args"]["Labels"] = labels;

        return doc.dump();
    }
   
    std::string ResponseJsonBuilder::CreateSettingsUpdateResponse(bool status, 
        const std::unordered_map<std::string, std::string>& values)
    {
        json doc;
        doc["cmd"] = "SettingsUpdateResponse";
        doc["status"] = status;
        doc["args"] = values;

        return doc.dump();
    }
} // namespace Networks


