#pragma once
#include "Networks/Command.h"

namespace Networks
{
    /*
    web -> server
    Header => CMD="Init"

    server -> web
    {
        "CMD": "InitResponse",
        "Args": {
            "ModelNames": ["yolov8n_sixray.onnx", "yolov5_dulray.onnx"],
            "Frameworks": ["OpenVINO", "ONNXRuntime"],
            "Algorithms": ["YOLOv3", "YOLOv5", "YOLOv8", "RT-DETR"],
            "CurrentModelIndex": 0,
            "CurrentFrameworkIndex": 0,
            "CurrentAlgorithmIndex": 2
        }
    }
    */


    class InitializeCommand: public Command
    {
    public:
        InitializeCommand() = default;
        ~InitializeCommand() = default;
        
        virtual std::string Execute(const HttpRequest& req) override;
    };
    
   
    
} // namespace Networks
