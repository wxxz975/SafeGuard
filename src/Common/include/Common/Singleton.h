#pragma once
#include <memory>
#include <mutex>

namespace Common
{
    template<typename T, typename ...Args>
    class Singleton
    {
    public:
        Singleton() = default;
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;

        static T* Instance(Args... args) {
             std::call_once(m_initFlag, [&] {
                m_instance.reset(new T(std::forward<Args>(args)...));
            });

            return m_instance.get();
        }

    private:
        static std::once_flag m_initFlag;    // 保证只调用一次
        static std::unique_ptr<T> m_instance; // 自动管理资源
    };

    // 静态成员初始化
    template<typename T, typename... Args>
    std::once_flag Singleton<T, Args...>::m_initFlag;

    template<typename T, typename... Args>
    std::unique_ptr<T> Singleton<T, Args...>::m_instance = nullptr;
} // namespace Common
