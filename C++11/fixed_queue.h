#ifndef _FIXED_QUEUE_H
#define _FIXED_QUEUE_H
#include<deque>
#include<exception>

template<typename T, size_t SIZE>
class FixedQueue
{
    std::deque<T> que;
public:
    void Enqueue(T& t)
    {
        que.push_back(t);
        if (que.size() >= SIZE)
        {
            que.pop_front();
        }
    }

    T Deque()
    {
        if (que.size() > 0)
        {
            T t = que.front();
            que.pop_front();
            return t;
        }

        throw bad_exception();
    }
};
#endif