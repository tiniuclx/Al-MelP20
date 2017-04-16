#include "serialreceiver.h"
#include <QDebug>
#include <math.h>

const int COORDINATE_BITS = 16;

serialReceiver::serialReceiver()
{
}

void serialReceiver::decoder(std::vector<bool> message){
    bool connected;
    int x=0;
    int y=0;
    unsigned int expectedSize = 34;
    if (message.size()==expectedSize){
        if (message[0]==true){
            qDebug()<<"Received: Drawing a point!";
            connected=message[1];
            //convert binary coordinate x into decimal
            for(int i=0; i<COORDINATE_BITS; i++){
                x=x+(((int)message[i+2] )*(pow(2,i)));
                y=y+(((int)message[i+18])*(pow(2,i)));
            }
            qDebug()<<x<<y<<connected;
        }
        else if (message[0]==false){
            qDebug()<<"Received: clear screen";
        }
    } else {
        qDebug()<<"Unexpected message of size:"<<message.size();
    }
}
