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


void* sendThread(void* thread_id)
{
    long tid = (long)thread_id;
    // do something....
    qDebug() << "Send thread " << tid << "started.";

    // end thread
    pthread_exit(NULL);
}

void* receiveThread(void* thread_id)
{
    long tid = (long)thread_id;
    // do something....
    qDebug() << "Receive thread " << tid << "started.";

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
    // the two windows are initialised in the main loop
    SendWindow s;
    ReceiveWindow r;

    SerialReceiver receiver(r.viewer);
    SerialSender sender(s.canvas, &receiver);

    s.show();
    r.show();

    // starting worker thread(s)
    int rc;
    pthread_t send_thread, receive_thread;
    rc = pthread_create(&send_thread, NULL, sendThread, (void*)1);
    if (rc) {
        qDebug() << "Unable to start send thread.";
        exit(1);
    }

    rc = pthread_create(&receive_thread, NULL, receiveThread, (void*)1);
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
