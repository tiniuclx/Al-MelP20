#include "serialreceiver.h"
#include <QDebug>
#include <math.h>

#define COORDINATE_BITS 16

serialReceiver::serialReceiver()
{
}

void serialReceiver::decoder(std::vector<bool> message){
    bool connected;
    int x;
    int y;

    if (message.size()==34){
        if (message[0]==1){
                connected=message[1];
                qDebug()<<connected;

                //convert binary coordinate x into decimal
                for(int i=0; i<COORDINATE_BITS; i++){
                    x=x+(((int)message[i+2])*(pow(2,i)));
                }
                qDebug()<<x;
        }
        else if (message[0]==0){
            qDebug()<<"cleared";
        }
    }
}
