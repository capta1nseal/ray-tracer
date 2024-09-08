#ifndef _RAYTRACERWORKQUEUE_
#define _RAYTRACERWORKQUEUE_


#include <mutex>
#include <tuple>


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

    // Set total number of tasks per iteration.
    void setTaskCount(unsigned int count);

    // Set task length.
    void setTaskLength(unsigned int length);

    // Get a tast from the queue.
    // If there are no tasks, returns -1.
    std::tuple<int, unsigned int> getTask();

private:
    unsigned int nextTask;
    unsigned int taskCount;
    unsigned int taskLength;

    // Just one mutex and lock_guards for thread safety.
    std::mutex accessMutex;

};


#endif
