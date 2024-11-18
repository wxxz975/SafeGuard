#include "Networks/ResponseJsonBuilder.h"

#include "Common/json.hpp"

namespace Networks
{
    using json = nlohmann::json;

    std::string ResponseJsonBuilder::CreateHisoryQueryResponse(bool status, const std::string& msg, const std::map<std::string, int>& statistic)
    {   
        json doc;
        doc["CMD"] = "HistoryQueryResponse";
        doc["Status"] = status;
        
        doc["Args"]["Message"] = msg;
        doc["Args"]["Statistic"] = statistic;

        return doc.dump();

        /*
            {
                "cmd":
                "status": bool
                "args": {
                    "Message": "",
                    "Statistic": {
                        [
                            {"Gun": 98},
                            {"Wrench": 10}
                        ]
                    }
                }
            }
        */
    }
    
    
    std::string ResponseJsonBuilder::CreateNewResultMessage(const std::string &filename, 
        const std::vector<Inference::Base::BoundingBox> &boxes, 
         std::shared_ptr<std::vector<std::string>> labels)
    {
        
        json doc;
        doc["CMD"] = "NewResultMessage";
        doc["Args"]["Filename"] = filename;
        
        auto& items = doc["Args"]["DetectedItem"];
        for(int idx = 0; idx < boxes.size(); ++idx) {
            int label_idx = boxes[idx].class_index;
            std::array<int, 4> coord = {boxes[idx].left, boxes[idx].top, boxes[idx].width, boxes[idx].height};
            items[idx]["Label"] = labels->at(label_idx);
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
        doc["CMD"] = "InitResponse";
        
        doc["Args"]["ModelNames"] = modelLists;
        doc["Args"]["Framworks"] = frameworkLists;
        doc["Args"]["Algorithms"] = algorithmLists;
        doc["Args"]["CurrentModelIndex"] = curModelIdx;
        doc["Args"]["CurrentFrameworkIndex"] = curFrameworkIdx;
        doc["Args"]["CurrentAlgorithmIndex"] = curAlgoIdx;

        return doc.dump();
    }
    
    std::string ResponseJsonBuilder::CreateModelSwitchResponse(
                bool status,
                const std::string& modelName, 
                const std::string& algo, const std::string& framework,
                const std::vector<std::string>& labels)
    {
        json doc;
        doc["CMD"] = "ModelSwitchResponse";
        doc["Args"]["ModelName"] = modelName;
        doc["Args"]["Framework"] = framework;
        doc["Args"]["Algorithm"] = algo;


        doc["Args"]["Labels"] = labels;

        return doc.dump();
    }
   
    std::string ResponseJsonBuilder::CreateSettingsUpdateResponse(bool status, 
        const std::unordered_map<std::string, std::string>& values)
    {
        json doc;
        doc["CMD"] = "SettingsUpdateResponse";
        doc["Status"] = status;
        doc["Args"] = values;

        return doc.dump();
    }

    std::string ResponseJsonBuilder::CreateModelInfoQueryResponse(bool status, std::string& modelname, std::shared_ptr<std::vector<std::string>> labels)
    {
        json doc;
        doc["CMD"] = "ModelInfoQueryResponse";
        doc["Status"] = status;
        doc["ModelName"] = modelname;
        doc["Args"]["Labels"] = labels ? (*labels) : std::vector<std::string>();

        return doc.dump();
    }

} // namespace Networks


