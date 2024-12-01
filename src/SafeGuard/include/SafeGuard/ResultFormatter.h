#pragma once
#include <string>
#include "Inference/Base/BoundingBox.h"
#include "Common/json.hpp"

namespace SafeGuard
{

    /*
        use websocket tranfer

        {
            "CMD": "NewResultMessage",
            "Args"{
                "Filename": "P001878.png",
                "DetectedItem": [
                    {
                        "Label": "Gun",
                        "Confidence": 0.998,
                        "Coordinate": [12, 21, 54, 97] // left, top, width, height
                    },
                    {
                        "Label": "Lighter",
                        "Confidence": 0.676,
                        "Coordinate": [2, 9, 74, 17] 
                    }
                ]
            }
        }
    */

    class ResultFormatter
    {
    public:
        ResultFormatter() = delete;
        ~ResultFormatter() = delete;

        static std::string Format(const std::string& filename, const Inference::Base::OutputBoxes& boxes, std::shared_ptr<std::vector<std::string>> labels);
    };
    
    
    
} // namespace SafeGuard
