#pragma once
#include <unordered_map>
#include <optional>


namespace Common
{
    // 用于双向查找key和value，不适合太大的数据结构
    template <typename K, typename V>
    class BiMap {
    public:
        // 默认构造函数
        BiMap() = default;

        // 通过初始化列表构造
        BiMap(std::initializer_list<std::pair<K, V>> init) {
            for (const auto& kv : init) {
                insert(kv.first, kv.second);
            }
        }

        // 插入键值对
        void insert(const K& key, const V& value) {
            // 添加到 key-value 映射
            m_keyToValue[key] = value;
            // 添加到 value-key 映射
            m_valueToKey[value] = key;
        }

       std::optional<V> operator[](const K& key) const {
           auto it = m_keyToValue.find(key);
           if (it != m_keyToValue.end()) {
               return it->second;
           }
           return std::nullopt; // 如果没有找到，返回空
       }

       std::optional<K> operator[](const V& value) const {
           auto it = m_valueToKey.find(value);
           if (it != m_valueToKey.end()) {
               return it->second;
           }
           return std::nullopt; // 如果没有找到，返回空
       }

        // 删除键值对
        void remove(const K& key) {
            auto it = m_keyToValue.find(key);
            if (it != m_keyToValue.end()) {
                m_valueToKey.erase(it->second); 
                m_keyToValue.erase(it); 
            }
        }
        void remove(const V& value) {
            auto it = m_valueToKey.find(value);
            if (it != m_valueToKey.end()) {
                m_keyToValue.erase(it->second); 
                m_valueToKey.erase(it); 
            }
        }

    private:
        std::unordered_map<K, V> m_keyToValue; // 键到值的映射
        std::unordered_map<V, K> m_valueToKey; // 值到键的映射
    };


} // namespace Common
