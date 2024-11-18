#pragma once
#include <string>
#include "Inference/Base/BoundingBox.h"
#include "Common/json.hpp"

namespace SafeGuard
{

    class ResultFormatter
    {
    public:
        ResultFormatter() = delete;
        ~ResultFormatter() = delete;

        static std::string Format(const std::string& filename, const Inference::Base::OutputBoxes& boxes, std::shared_ptr<std::vector<std::string>> labels);
    };
    
    
    
} // namespace SafeGuard
