#include "workqueue.hpp"


WorkQueue::WorkQueue()
{
}
WorkQueue::~WorkQueue()
{
}

void WorkQueue::clearQueue()
{
    std::lock_guard<std::mutex> lock(accessMutex);

    tasks.clear();
}

void WorkQueue::queueTasks(unsigned int count)
{
    clearQueue();

    std::lock_guard<std::mutex> lock(accessMutex);

    for (unsigned int i = 0u; i < count; i++)
    {
        tasks.push_back(i);
    }
}

int WorkQueue::getTask()
{
    unsigned int task;
    {
        std::lock_guard<std::mutex> lock(accessMutex);

        if (tasks.size() == 0) return -1;

        task = tasks.front();
        tasks.pop_front();
    }
    return task;
}
