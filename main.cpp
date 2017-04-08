#include <QApplication>
#include <QDebug>

#include <pthread.h>
#include <wiringPi.h>

#include "window.h"

void* worker(void* thread_id)
{
    long tid = (long)thread_id;
    // do something....
    qDebug() << "Worker thread " << tid << "started.";

    // end thread
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
    Window w;
    w.show();

    // starting worker thread(s)
    int rc;
    pthread_t worker_thread;
    rc = pthread_create(&worker_thread, NULL, worker, (void*)1);
    if (rc) {
        qDebug() << "Unable to start worker thread.";
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
