#include "workqueue.hpp"


#include <mutex>


WorkQueue::WorkQueue()
{
    nextTask = 0;
}
WorkQueue::~WorkQueue()
{
}

void WorkQueue::queueTasks(unsigned int count)
{
    std::lock_guard<std::mutex> lock(accessMutex);

    taskCount = count;

    nextTask = 0;
}

int WorkQueue::getTask()
{
    unsigned int task;

    {
        std::lock_guard<std::mutex> lock(accessMutex);

        if (nextTask >= taskCount)
        {
            task = -1;
        }
        else
        {
            task = nextTask;
            nextTask++;
        }
    }

    return task;
}
