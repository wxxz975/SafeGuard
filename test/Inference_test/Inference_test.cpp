#include <string>
#include <iostream>
#include <unordered_map>
#include "Common/IFilesystem.h"
#include "Inference/InferenceEngine.h"




int main(int argc, char* argv[]) 
{
    std::string img_path = "/home/wxxz/workspace/datasets/coco128/images/train2017/000000000257.jpg";
    
    std::string model_root_dir = "/home/wxxz/workspace/weights/COCO";
    std::unordered_map<std::string, std::string> algo2models =
    {   
        {"YOLOv3", "yolov3-tinyu.onnx"},
        {"YOLOv5", "yolov5s6u.onnx"},
        {"YOLOv8", "yolov8s.onnx"},
        {"RTDetr", "rtdetr-l.onnx"}
    };
    using namespace Common::IFilesystem;
    for(auto& iter : algo2models) {
        std::string realpath = ConcatPath(ConcatPath(model_root_dir, iter.first), iter.second);
        iter.second = realpath;
    }

    

    std::vector<std::string> frameworks = {"OpenVINO", "ONNXRuntime"};
    
    for(const auto& framework : frameworks) {
        
        for(const auto& model : algo2models) {
            std::string model_name = model.first;
            std::string model_path = model.second;

            std::cout << "test framework:" << framework 
                << "test model:" << model_name << 
                " model path:" << model_path<< "\n";
            
            Inference::InferenceEngine engine;
            if(engine.Initialize(model_path, model_name, framework)){
                std::cout << "initialize success!\n";

                auto result = engine.Infer(img_path);
                cv::Mat rendered = engine.RenderBoxes(img_path, result);
                std::string save_path = framework + model_name + GetFilename(img_path);
                cv::imwrite(save_path, rendered);

                std::cout << GetFilename(img_path) << "inference result:\n"; 
                for(const auto& iter : result) {
                    std::cout << iter;
                }
            }

        }
        
    }

    return 0;
}
