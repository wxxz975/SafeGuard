#pragma once
#include <queue>
#include <mutex>
#include <optional>


namespace Common
{
    template<typename T>
    class SafeQueue
    {
        typedef std::queue<T> QueueType;
    public:
        SafeQueue() {

        }
        ~SafeQueue() {

        }

        void Put(const T& value)
        {
            std::unique_lock<std::mutex> locker(m_mtx);
            m_queue.push(value);
        }

        void Put(T&& value) {
            std::unique_lock<std::mutex> locker(m_mtx);
            m_queue.push(std::move(value));
        }

        std::optional<T> Take()
        {
            std::unique_lock<std::mutex> locker(m_mtx);
            if(!m_queue.empty()) {
                T front(std::move(m_queue.front()));
                m_queue.pop();
                return std::optional<T>(front);
            }

            return std::nullopt;
        }

        std::optional<T> Drain()
        {
            QueueType queue;
            {
                std::unique_lock<std::mutex> locker(m_mtx);
                queue = std::move(m_queue);
            }

            return queue;
        }


        size_t Size() {
            std::unique_lock<std::mutex> locker(m_mtx);
            return m_queue.size();
        }

        bool Empty() {
            return !Size();
        }

    private:
        std::queue<T> m_queue;
        std::mutex m_mtx;
    };
    
    
    
} // namespace Common
