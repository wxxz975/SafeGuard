#pragma once
#include <string>
#include <vector>
#include "ElementType.h"


namespace Inference
{
    namespace Base
    {
        struct IOInfo
        {
            std::string name;
            ElementType type;
            std::vector<std::uint64_t> shape;
            IOInfo(const std::string& name, Type_t type, const std::vector<std::uint64_t>& shape) :
                name(name), type(type), shape(shape) {};

            IOInfo(Type_t type) : type(type) {

            }

            IOInfo() : name("None"), type(Type_t::f32) {

            }

            IOInfo(const std::vector<std::uint64_t>& shape) : shape(shape) {

            }

            IOInfo(Type_t type, const std::vector<std::uint64_t>& shape, const std::string& name = "None") :
                type(type), shape(shape), name(name)
            {

            }
        };

        struct ModelMetadata
        {
            // 对应onnx模型中的inputs
            std::vector<IOInfo> inputs;

            // 对应onnx模型中的outpus
            std::vector<IOInfo> outputs;

            // 对应onnx模型中的model metadata
            std::unordered_map<std::string, std::string> metadata;

            // 对应onnx模型中的model properties
            std::unordered_map<std::string, std::string> properties;

            // 模型中的标签，可能存在携带
            std::vector<std::string> labels;

            size_t GetInputCount() const { return inputs.size(); };
            size_t GetOutputCount() const { return outputs.size(); };

        };

    } // namespace Base
    

} // namespace Inference
