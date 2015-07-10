#ifndef _ALI_SR_BLOCK_QUEUE_H
#define _ALI_SR_BLOCK_QUEUE_H
#include <mutex>
#include <condition_variable>
#include <deque>

template<typename T>
class BlockQueue
{
    std::mutex mtx;
    std::condition_variable cv;
    std::deque<T> queue;
public:
    void AddItem(const T& item)
    {
        std::unique_lock<std::mutex> lock(mtx);
        queue.push_back(item);
        cv.notify_one();
    }

    void GetItem(T& item)
    {
        std::unique_lock<std::mutex> lock(mtx);
        while (queue.size() == 0) {
            cv.wait(lock);
        }

        item = queue.front();
        queue.pop_front();
    }
};

#endif