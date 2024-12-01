#pragma once
#include "Networks/Command.h"


namespace Networks
{

    /*
        web -> server
        header => "CMD" = "QuerySwitchModel"
        params => "ModelName" = "yolov8_sixray.onnx"


        server -> web
        {
            "CMD": "ModelInfoQueryResponse",
            "Status": true,
            "ModelName": "yolov8_sixray.onnx",
            "Args": {
                "Labels" : ["Gun", "Lighter", "Wrench"]
            }
        }
    */

    class ModelInfoQueryCommand: public Command
    {
    public:
        ModelInfoQueryCommand() = default;
        ~ModelInfoQueryCommand() = default;

        virtual std::string Execute(const HttpRequest& req) override;
    };
    
    
    
    
} // namespace Networks
