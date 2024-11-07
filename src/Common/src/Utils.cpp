#include "Common/Utils.h"
#include <algorithm>
#include <ctime>
#include <iomanip>

namespace Common
{

    std::pair<std::size_t, float> FindMaxIndexValue(std::vector<float>::iterator& iter, std::size_t num_class)
    {
        auto maxElement = std::max_element(iter, iter + num_class);
        std::size_t maxIndex = std::distance(iter, maxElement);
        float maxValue = *maxElement;

        return { maxIndex, maxValue };
    }

    std::pair<std::size_t, float> FindMaxIndexValue(float* data, std::size_t num_class)
    {
        auto maxElement = std::max_element(data, data + num_class);
        std::size_t maxIndex = std::distance(data, maxElement);
        float maxValue = *maxElement;

        return { maxIndex, maxValue };
    }

    std::vector<std::string> ParseJsonRaw(const std::string &raw_json)
    {
        std::vector<std::string> labels;

        // 正则表达式模式
        std::regex pattern("'([^']*)'");

        // 迭代器对正则表达式进行匹配
        std::sregex_iterator it(raw_json.begin(), raw_json.end(), pattern);
        std::sregex_iterator end;

        while (it != end) {
            std::smatch match = *it;
            std::string value = match[1].str();
            labels.push_back(value);
            ++it;
        }

        return labels;
    }

    std::string GetCurrentTimestamp() {
        auto now = std::time(nullptr);
        std::tm localTime;
    #ifdef _WIN32
        localtime_s(&localTime, &now); // Windows
    #else
        localtime_r(&now, &localTime); // Unix/Linux
    #endif

        std::ostringstream oss;
        oss << std::put_time(&localTime, "%Y%m%d_%H%M%S");
        return oss.str();
    }
    
} // namespace Common
