#ifndef _RAYTRACERWORKQUEUE_
#define _RAYTRACERWORKQUEUE_


#include <mutex>


/*
Simple queue to coordinate multithreading.
Queue is actually faked with a rolling uint, since jobs are always fetched in sequential order
All operations are thread-safe.
*/
class WorkQueue
{
public:
    WorkQueue();
    ~WorkQueue();

    // Add numbers 0->(count-1) to queue.
    void queueTasks(unsigned int count);

    // Get a tast from the queue.
    // If there are no tasks, returns -1.
    int getTask();

private:
    unsigned int nextTask;
    unsigned int taskCount;

    // Just one mutex and lock_guards for thread safety.
    std::mutex accessMutex;

};


#endif
