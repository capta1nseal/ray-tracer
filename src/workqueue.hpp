#ifndef _RAYTRACERWORKQUEUE_
#define _RAYTRACERWORKQUEUE_


#include <mutex>
#include <condition_variable>


/*
Simple queue to coordinate multithreading.
Queue is actually faked with a rolling uint, since jobs are always fetched in sequential order.
All operations are thread-safe.
*/
class WorkQueue
{
public:
    WorkQueue();
    ~WorkQueue();

    // Forget current task and go back to the first task.
    void toFirstTask();

    // Inform queue of total number of tasks.
    void setTaskCount(unsigned int count);

    // Allow the queue to give out <count> number of all tasks.
    void queueRepetitions(unsigned int count);

    // Get a task from the queue.
    // If there are no tasks, returns -1.
    int getTask();

    // Wait for more work to be added to the queue.
    void waitForWork();

    // Wait until all queued work is finished.
    void waitTillDone();

private:
    unsigned int nextTask;
    unsigned int taskCount;
    unsigned int repetitions;

    // Flag for whether work is done, or ongoing.
    bool workDone;

    // Just one mutex and lock_guards for thread safety.
    std::mutex accessMutex;

    // Used to signal when more work is queued.
    std::condition_variable workCondition;

    // Used to signal when work is complete.
    std::condition_variable doneCondition;
};


#endif
