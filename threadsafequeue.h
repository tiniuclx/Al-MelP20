#ifndef THREADSAFEQUEUE_H
#define THREADSAFEQUEUE_H
#include <queue>
#include <vector>
#include <pthread.h>
#include <QDebug>
class ThreadSafeQueue
{
public:
    ThreadSafeQueue();
    ~ThreadSafeQueue();
    uint size();
    std::vector<bool> front();
    void pop();
    void push(std::vector<bool> val);
    // Prints the front element of the queue
    void print(void);
private:
    std::queue<std::vector<bool> > queue;
    pthread_mutex_t mutex;
};

#endif // THREADSAFEQUEUE_H
