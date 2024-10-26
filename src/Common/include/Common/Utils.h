#pragma once
#include <vector>
#include <cstdint>
#include <string>
#include <sstream>
#include <type_traits>
#include <iterator>
#include <regex>

namespace Common
{
    template <typename TargetType, typename SourceContainer>
    std::vector<TargetType> VecToVec(const SourceContainer& source) 
    {
        using SourceType = typename std::decay<decltype(*std::begin(source))>::type;

        static_assert(std::is_arithmetic<TargetType>::value && std::is_arithmetic<SourceType>::value, 
                    "TargetType and SourceType must be arithmetic types");

        std::vector<TargetType> result;
        result.reserve(std::distance(std::begin(source), std::end(source))); // 预分配空间以提高性能

        for (const auto& value : source) {
            result.push_back(static_cast<TargetType>(value));
        }

        return result;
    }




    template <typename T>
    std::string VecToStr(const std::vector<T>& vec) {
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < vec.size(); ++i) {
            oss << vec[i];
            if (i < vec.size() - 1) {
                oss << ", ";  // 添加逗号分隔符
            }
        }
        oss << "]";  // 关闭方括号
        return oss.str();
    }

    template<typename T>
    bool CompareVecWithMask(const std::string &mask, const std::vector<T> &shape1, const std::vector<T> &shape2)
    {
        if((mask.size() != shape1.size()) || (mask.size() != shape2.size()))
            return false;

        for(int idx = 0; idx < mask.size(); ++idx) {
            if(mask[idx] == '?') continue;
            if(shape1[idx] != shape2[idx]) {
                return false;
            }
        }

        return true;
    }

    std::pair<std::size_t, float> FindMaxIndexValue(std::vector<float>::iterator& iter, std::size_t num_class);

    std::pair<std::size_t, float> FindMaxIndexValue(float* data, std::size_t num_class);


    // 解析非标准的json数据，key不是字符串类型 
    std::vector<std::string> ParseJsonRaw(const std::string &raw_json);

} // namespace Common
