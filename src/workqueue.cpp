#include "workqueue.hpp"


#include <mutex>
#include <condition_variable>


WorkQueue::WorkQueue()
{
    std::lock_guard<std::mutex> lock(accessMutex);

    nextTask = 0u;
    taskCount = 0u;
    repetitions = 0u;

    workDone = true;
}
WorkQueue::~WorkQueue()
{
}

void WorkQueue::toFirstTask()
{
    std::lock_guard<std::mutex> lock(accessMutex);

    nextTask = 0u;
}

void WorkQueue::setTaskCount(unsigned int count)
{
    std::lock_guard<std::mutex> lock(accessMutex);

    taskCount = count;
}

void WorkQueue::queueRepetitions(unsigned int count)
{
    std::lock_guard<std::mutex> lock(accessMutex);

    repetitions += count;

    workDone = false;

    workCondition.notify_all();
}

int WorkQueue::getTask()
{
    unsigned int task;

    {
        std::lock_guard<std::mutex> lock(accessMutex);

        if (repetitions == 0u) return -1;

        task = nextTask;

        nextTask++;

        if (nextTask >= taskCount)
        {
            nextTask = 0u;
            repetitions--;

            if (repetitions == 0u)
            {
                workDone = true;

                doneCondition.notify_all();
            }
        }
    }

    return task;
}

void WorkQueue::waitForWork()
{
    std::unique_lock<std::mutex> waitLock(accessMutex);

    if (workDone == false) return;

    workCondition.wait(waitLock, [this]{return workDone == false;});
}

void WorkQueue::waitTillDone()
{
    std::unique_lock<std::mutex> waitLock(accessMutex);

    if (repetitions == 0u) return;

    doneCondition.wait(waitLock, [this]{return workDone;});
}
