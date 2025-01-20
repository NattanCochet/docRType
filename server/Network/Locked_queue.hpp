#include <boost/thread/mutex.hpp>
#include <list>
#include <queue>

#pragma once

template <typename T> class LockedQueue {
  private:
    boost::mutex mutex;
    std::queue<T> queue;

    void remove_if(const std::function<bool(const T&)>& condition) {
        std::deque<T> temp;

        while (!queue.empty()) {
            T value = std::move(queue.front());
            queue.pop();

            if (!condition(value)) {
                temp.push_back(std::move(value));
            }
        }

        for (auto& value : temp) {
            queue.push(std::move(value));
        }
    }

  public:
    std::size_t max_size;

    explicit LockedQueue(std::size_t max_size = 1000) : max_size(max_size) {}
    void push(T value)
    {
        boost::mutex::scoped_lock lock(mutex);

        // if (queue.size() >= max_size) {
        //     queue.pop();
        // }
        queue.push(std::move(value));
    };

    T pop()
    {
        boost::mutex::scoped_lock lock(mutex);
        if (queue.empty()) {
            throw std::runtime_error("Attempt to pop from an empty queue");
        }
        T value = std::move(queue.front());
        queue.pop();
        return value;
    }

    T peek() {
        boost::mutex::scoped_lock lock(mutex);
        if (queue.empty()) {
            throw std::runtime_error("Attempt to peek into an empty queue");
        }
        return queue.front();
    }

    bool pop_if(const std::function<bool(const T&)>& condition) {
        boost::mutex::scoped_lock lock(mutex);
        if (!queue.empty() && condition(queue.front())) {
            queue.pop();
            return true;
        }
        return false;
    }

    bool empty()
    {
        boost::mutex::scoped_lock lock(mutex);
        return queue.empty();
    }

    std::size_t size()
    {
        boost::mutex::scoped_lock lock(mutex);
        return queue.size();
    }
};
