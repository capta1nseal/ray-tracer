#ifndef _RAYTRACERWORKQUEUE_
#define _RAYTRACERWORKQUEUE_


#include <mutex>
#include <queue>


/*
Simple queue to coordinate multithreading.
Currently only stores one integer for each job, and the numbers are sequentially generated.
All operations are thread-safe.
*/
class WorkQueue
{
public:
    WorkQueue();
    ~WorkQueue();

    // Empty the queue.
    void clearQueue();

    // Add numbers 0->(count-1) to queue.
    void queueTasks(unsigned int count);

    // Get a tast from the queue.
    // If there are no tasks, returns -1.
    int getTask();

private:
    // Deque is probably overkill.
    std::deque<unsigned int> tasks;

    // Just one mutex and lock_guards for thread safety.
    std::mutex accessMutex;

};


#endif
