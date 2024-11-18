#include "Common/Utils.h"
#include <algorithm>
#include <chrono>
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

    std::shared_ptr<std::vector<std::string>> ParseJsonRaw(const std::string &raw_json)
    {
        std::shared_ptr<std::vector<std::string>> labels = std::make_shared<std::vector<std::string>>();

        // 正则表达式模式
        std::regex pattern("'([^']*)'");

        // 迭代器对正则表达式进行匹配
        std::sregex_iterator it(raw_json.begin(), raw_json.end(), pattern);
        std::sregex_iterator end;

        while (it != end) {
            std::smatch match = *it;
            std::string value = match[1].str();
            labels->push_back(value);
            ++it;
        }

        return labels;
    }


    std::string DateToTimestamp(const std::string& dateStr) {
        std::tm tm = {};
        std::istringstream ss(dateStr);

        // 解析日期格式 YYYY-MM-DD
        ss >> std::get_time(&tm, "%Y-%m-%d");
        if (ss.fail()) {
            return "";  // 转换失败，返回空字符串
        }

        // 使用 chrono 将 tm 转换为 time_point
        std::chrono::system_clock::time_point tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
        auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch()).count();

        // 将时间戳转换为字符串并返回
        return std::to_string(timestamp);
    }

    std::string GetCurrentTimestamp() {
        // 获取当前时间点并转换为 time_t
        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();

        // 将时间戳转换为字符串并返回
        return std::to_string(timestamp);
    }

} // namespace Common
