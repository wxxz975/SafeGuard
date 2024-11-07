#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include "Framework.h"

#include "FrameworkImpl.h"

#include "Inference/SupportedFrameworks.h"

namespace Inference
{
    namespace LowerFramework
    {
        class LowerFrameworkFactory
        {
        public:
            LowerFrameworkFactory() = delete;
            ~LowerFrameworkFactory() = delete;

            static std::unique_ptr<FrameworkImpl> CreateFramework(FrameworkType framework);

            static std::unique_ptr<FrameworkImpl> CreateFramework(const std::string& framework);

        
        };
        
    } // namespace LowerFramework
    
    
} // namespace Inference
