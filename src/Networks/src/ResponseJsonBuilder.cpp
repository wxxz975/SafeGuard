#include "ResponseJsonBuilder.h"

std::string ResponseJsonBuilder::buildNewImageResponse(const std::string &filename, 
    const std::vector<BoundingBox> &boxes, 
    const std::vector<std::string>& labels)
{
    json doc;
    doc["cmd"] = "QueryResultResponse";
    doc["args"]["OriginalImage"] = filename;
    
    auto& items = doc["args"]["DetectedItem"];
    for(int idx = 0; idx < boxes.size(); ++idx) {
        int label_idx = boxes[idx].class_index;
        std::array<int, 4> coord = {boxes[idx].left, boxes[idx].top, boxes[idx].width, boxes[idx].height};
        items[idx]["label"] = labels[label_idx];
        items[idx]["confidence"] = boxes[idx].confidence;
        items[idx]["coordinate"] = coord;
    }
    
    if(!boxes.size()) items = std::vector<int>();
    
    return doc.dump();
}

std::string ResponseJsonBuilder::buildInitResponse(const std::vector<std::string>& modelLists)
{
    json doc;
    doc["cmd"] = "InitResponse";
    
    doc["args"]["ModelNames"] = modelLists;

    return doc.dump();
}

std::string ResponseJsonBuilder::buildLoadingModelResponse(const std::string &modelName, 
    const std::vector<std::string> &labels)
{
    json doc;
    doc["cmd"] = "SwitchResponse";
    doc["args"]["ModelName"] = modelName;


    std::map<std::string, int> statistics;
    for(const auto& name : labels)
        statistics[name] = 0;

    doc["args"]["label"] = labels;
    doc["args"]["statistics"] = statistics;

    return doc.dump();
}
