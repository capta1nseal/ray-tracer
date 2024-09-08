#include "workqueue.hpp"


#include <mutex>
#include <tuple>


WorkQueue::WorkQueue()
{
    nextTask = 0;
    taskCount = 0;
    taskLength = 0;
}
WorkQueue::~WorkQueue()
{
}

void WorkQueue::setTaskCount(unsigned int count)
{
    std::lock_guard<std::mutex> lock(accessMutex);

    taskCount = count;

    nextTask = 0;
}

void WorkQueue::setTaskLength(unsigned int length)
{
    std::lock_guard<std::mutex> lock(accessMutex);

    taskLength = length;
}

std::tuple<int, unsigned int> WorkQueue::getTask()
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

    return {task, taskLength};
}
