#include "threadsafequeue.h"

void errorCheck(int error){
    if(error!=0){
        qDebug()<<"Mutex failed!";
    }
}

ThreadSafeQueue::ThreadSafeQueue()
{
    pthread_mutex_init(&mutex, NULL);

}
ThreadSafeQueue::~ThreadSafeQueue(){
    pthread_mutex_destroy(&mutex);
}

void ThreadSafeQueue::pop() {
    errorCheck(pthread_mutex_lock(&mutex));
    queue.pop();
    errorCheck(pthread_mutex_unlock(&mutex));
}

void ThreadSafeQueue::push(std::vector<bool> val){
    errorCheck(pthread_mutex_lock(&mutex));
    queue.push(val);
    errorCheck(pthread_mutex_unlock(&mutex));
}

void ThreadSafeQueue::print(){
    errorCheck(pthread_mutex_lock(&mutex));
    std::vector<bool> bitfield = queue.front();
    errorCheck(pthread_mutex_unlock(&mutex));
    QDebug deb = qDebug();
    for(uint i=0;i<bitfield.size();i++){
        bool bit = bitfield[i];
        deb<<bit;
    }
}

std::vector<bool> ThreadSafeQueue::front(){
    std::vector<bool> data;
    errorCheck(pthread_mutex_lock(&mutex));
    data = queue.front();
    errorCheck(pthread_mutex_unlock(&mutex));
    return data;
}

uint ThreadSafeQueue::size(){
    errorCheck(pthread_mutex_lock(&mutex));
    uint size = queue.size();
    errorCheck(pthread_mutex_unlock(&mutex));
    return size;
}
