#ifndef _RAYTRACERWORKQUEUE_
#define _RAYTRACERWORKQUEUE_


#include <mutex>
#include <queue>


class WorkQueue
{
public:
    WorkQueue();
    ~WorkQueue();

    void clearQueue();

    void queueTasks(unsigned int count);

    int getTask();

private:
    std::deque<unsigned int> tasks;

    std::mutex accessMutex;

};


#endif
