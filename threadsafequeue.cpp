#include "threadsafequeue.h"

ThreadSafeQueue::ThreadSafeQueue()
{
    pthread_mutex_init(&mutex, NULL);

}
ThreadSafeQueue::~ThreadSafeQueue(){
    pthread_mutex_destroy(&mutex);
}

void ThreadSafeQueue::pop() {
    pthread_mutex_lock(&mutex);
    queue.pop();
    pthread_mutex_unlock(&mutex);
}

void ThreadSafeQueue::push(std::vector<bool> val){
    pthread_mutex_lock(&mutex);
    queue.push(val);
    pthread_mutex_unlock(&mutex);
}
