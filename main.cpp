#include <QWidget>
#include <QApplication>
#include <QDebug>

#include <pthread.h>
#include <wiringPi.h>

#include <vector>
#include <queue>

#include "sendwindow.h"
#include "receivewindow.h"
#include "serialsender.h"
#include "threadsafequeue.h"

struct thread_data{
    ThreadSafeQueue *receive_queue;
    ThreadSafeQueue *send_queue;
};

void printBool(const std::vector<bool> array){
    QDebug deb = qDebug();
    for(uint i=0;i<array.size();i++)
        qDebug()<<array[i];

}


void* sendThread(void* information)
{
    thread_data *data = (thread_data*) information;

    while(1){
        if(data->send_queue->size() != 0){
            std::vector<bool> bitfield = data->send_queue->front();
            qDebug()<<"Popped from send_queue by sendThread:";
            printBool(bitfield);
            data->send_queue->pop();
            data->receive_queue->push(bitfield);
        }
    }
    // end thread
    pthread_exit(NULL);
}

void* receiveThread(void* information)
{
    thread_data *data = (thread_data*) information;

    while(1){
        uint size = data->receive_queue->size();
        if(size!=0){            
            std::vector<bool> bitfield;
            bitfield = data->receive_queue->front();
            qDebug()<<"Popped from receive_queue by receiveThread:";
            printBool(bitfield);
            data->receive_queue->pop();
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    // setup GPIO interface - uncomment when needed
    // needs to run with root via sudo in terminal.
    //wiringPiSetup();
    //pinMode (0, OUTPUT);

    // setup Qt GUI
    QApplication a(argc, argv);
    // the two windows are initialised in the main loop
    SendWindow s;
    ReceiveWindow r;

    SerialReceiver receiver(r.viewer);
    SerialSender sender(s.canvas, &receiver);

    s.show();
    r.show();

    thread_data data;
    ThreadSafeQueue receive_queue;
    ThreadSafeQueue send_queue;
    data.receive_queue = &receive_queue;
    data.send_queue = &send_queue;

    std::vector<bool> stuff;
    stuff.push_back(1);
    stuff.push_back(0);
    stuff.push_back(1);
    stuff.push_back(1);
    qDebug()<<"Pushing stuff in main:";
    printBool(stuff);
    data.send_queue->push(stuff);

    stuff.push_back(0);
    qDebug()<<"Pushing stuff in main:";
    printBool(stuff);
    data.send_queue->push(stuff);

    // starting worker thread(s)
    int rc;
    pthread_t send_thread, receive_thread;
    rc = pthread_create(&send_thread, NULL, sendThread, (void*)&data);
    if (rc) {
        qDebug() << "Unable to start send thread.";
        exit(1);
    }

    rc = pthread_create(&receive_thread, NULL, receiveThread, (void*) &data.receive_queue);
    if (rc) {
        qDebug() << "Unable to start receive thread.";
        exit(1);
    }


    // start window event loop
    qDebug() << "Starting event loop...";
    int ret = a.exec();
    qDebug() << "Event loop stopped.";

    // cleanup pthreads
    pthread_exit(NULL);

    // exit
    return ret;
}
