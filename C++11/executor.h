#ifndef _ALI_SR_EXECUTOR_H
#define _ALI_SR_EXECUTOR_H
#include"block_queue.h"
#include<thread>
#include<functional>

enum class OperateType
{
    Init,
    Start,
    Data,
    End,
    Release,
};

struct ExeItem
{
    OperateType op;
    std::function<void(void)> execute_func = []() {};
    std::function<void(void)> final_execute_func = []() {};
};

class Executor
{
    BlockQueue<ExeItem> queue;
    std::thread executor_thread;

    void Run()
    {
        while (true)
        {
            ExeItem item;
            queue.GetItem(item);

        }
    }
public:
    Executor()
    {
        auto thread_func = [this]() 
        {return 0; };
        this->executor_thread = std::thread(thread_func);
    }

    void Execute(const ExeItem& item)
    {
        queue.AddItem(item);
    }
};
#endif