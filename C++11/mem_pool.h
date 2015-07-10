#ifndef _ALI_SR_MEM_POOL_H
#define _ALI_SR_MEM_POOL_H

#include<mutex>
#include<vector>
template<typename T, int N>
class MemPool
{
    std::mutex mtx;
    std::vector<T*> pool;
public:
    T* Allocate()
    {
        std::lock_guard<std::mutex> lck(mtx);
        T* ret = nullptr;
        if (pool.size() == 0)
        {
            ret = new T[N];
        }
        else
        {
            ret = pool.back();
            pool.pop_back();
        }

        return ret;
    }

    T* Copy(T* buf, size_t len)
    {
        if (len > N)
        {
            return nullptr;
        }

        T* new_buf = Allocate();
        memcpy(new_buf, buf, len);
        return new_buf;
    }

    void Free(T* buf)
    {
        std::lock_guard<std::mutex> lck(mtx);
        pool.push_back(buf);
    }

    ~MemPool()
    {
        for (size_t i = 0; i < pool.size(); i++)
        {
            if (pool[i] != nullptr)
            {
                delete pool[i];
            }
        }

        pool.clear();
    }
};
#endif