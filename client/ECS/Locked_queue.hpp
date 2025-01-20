#include <boost/thread/mutex.hpp>
#include <list>
#include <queue>

#pragma once

template <typename T> class LockedQueue {
  private:
    boost::mutex mutex;
    std::queue<T> queue;
    std::size_t max_size;

  public:
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
