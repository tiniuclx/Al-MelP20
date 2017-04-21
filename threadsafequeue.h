#ifndef THREADSAFEQUEUE_H
#define THREADSAFEQUEUE_H
#include <queue>
#include <vector>
#include <pthread.h>
class ThreadSafeQueue
{
public:
    ThreadSafeQueue();
    ~ThreadSafeQueue();
    int size() {
        return queue.size();
    }
    std::vector<bool> front(){
        return queue.front();
    }
    void pop();
    void push(std::vector<bool> val);
private:
    std::queue<std::vector<bool> > queue;
    pthread_mutex_t mutex;
};

#endif // THREADSAFEQUEUE_H
