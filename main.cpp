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
#include "serialreceiver.h"
#include "threadsafequeue.h"
#include "flaggedqpoint.h"

struct SerialPins{
    int data;
    int isSending;
    int hasRead;
};
// Structure containing the data passed to each thread
struct thread_data{
    ThreadSafeQueue *send_queue;
    SerialReceiver *receiver;
    SerialPins *serial_pins;
};
// Stub to implement simulated serial.
// Makes it easy to use physical pins: simply modify this function
int readPin(const int &pin){
    return digitalRead(pin);
}
// Stub to implement simulated serial.
// Makes it easy to use physical pins: simply modify this function
void writePin(const int &pin, const int value){
    digitalWrite(pin, value);
}
// For debugging purposes: prints out the values of a vector<bool>
// to qDebug()
void printBool(const std::vector<bool> array){
    QDebug deb = qDebug();
    for(uint i=0;i<array.size();i++)
        deb<<(int) array[i];
}

void* sendThread(void* information) {
    // Cast the void pointer to a pointer of the expected type
    thread_data *data = (thread_data*) information;
    while(1){
        // If the send queue is empty
        if(data->send_queue->size() != 0){
            // Pop out a message
            std::vector<bool> bitfield = data->send_queue->front();
            data->send_queue->pop();
            // Send the message over serial
            for(unsigned int i = 0; i<bitfield.size(); i++){
                writePin(data->serial_pins->data, bitfield[i]);
                writePin(data->serial_pins->isSending, TRUE);
                while(!readPin(data->serial_pins->hasRead))
                    ;
                writePin(data->serial_pins->isSending, FALSE);
                while(readPin(data->serial_pins->hasRead))
                    ;
            }
        }
    }
    // end thread
    pthread_exit(NULL);
}

void* receiveThread(void* information) {
    thread_data *data = (thread_data*) information;    
    std::vector<bool> bitfield;
    while(1){
        // When remote stops sending, make read
        // confirmation flag LOW
        while(readPin(data->serial_pins->isSending))
            ;
        writePin(data->serial_pins->hasRead, FALSE);
        while(!readPin(data->serial_pins->isSending))
            ;
        bitfield.push_back(readPin(data->serial_pins->data));
        // If the message has the right size
        if(bitfield.size() == SerialSender::messageSize() ){
            // Tells Viewer to draw the point, serialised as bitfield.
            data->receiver->decoder(bitfield);
            bitfield.clear();
        }
        writePin(data->serial_pins->hasRead, TRUE);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    // setup GPIO interface - uncomment when needed
    // needs to run with root via sudo in terminal.
    wiringPiSetup();

    // setup Qt GUI
    QApplication a(argc, argv);
    qRegisterMetaType<FlaggedQPoint>();
    // the two windows are initialised in the main loop    
    SendWindow s;
    ReceiveWindow r;
    s.show();
    r.show();
    // Data shared between threads
    thread_data send_data;
    thread_data receive_data;
    ThreadSafeQueue send_queue;
    // Serialization classes
    SerialReceiver receiver(r.viewer);
    SerialSender sender(s.canvas, &receiver,&send_queue);
    // Sets up thread data
    send_data.send_queue = &send_queue;
    send_data.receiver = &receiver;

    // Pins used for sending data to the remote
    // Physical pins 8, 10, 12
    SerialPins send_serial_pins;
    send_serial_pins.data = 15;
    send_serial_pins.isSending = 16;
    send_serial_pins.hasRead = 1;
    pinMode(send_serial_pins.data, OUTPUT);
    pinMode(send_serial_pins.isSending, OUTPUT);
    pinMode(send_serial_pins.hasRead, INPUT);
    send_data.serial_pins = &send_serial_pins;

    // Pins used for receiving data from the remote
    // Physical pins 22, 24, 26
    // Can switch the data and isSending pins around, to connect
    // two Pis more easily
    receive_data = send_data;
    SerialPins receive_serial_pins;
    receive_serial_pins.data = 6;
    receive_serial_pins.isSending = 10;
    receive_serial_pins.hasRead = 11;
    pinMode(receive_serial_pins.data, INPUT);
    pinMode(receive_serial_pins.isSending, INPUT);
    pinMode(receive_serial_pins.hasRead, OUTPUT);
    receive_data.serial_pins = &receive_serial_pins;

    // starting worker thread(s)
    int rc;
    pthread_t send_thread, receive_thread;
    rc = pthread_create(&send_thread, NULL, sendThread, (void*)&send_data);
    if (rc) {
        qDebug() << "Unable to start send thread.";
        exit(1);
    }
    rc = pthread_create(&receive_thread, NULL, receiveThread, (void*) &receive_data);
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
