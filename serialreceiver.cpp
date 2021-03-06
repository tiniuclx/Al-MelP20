#include "serialreceiver.h"
#include <QDebug>
#include <QObject>
#include <math.h>

const int COORDINATE_BITS = 10;

SerialReceiver::SerialReceiver(Viewer *viewer)
{
    QObject::connect(this,&SerialReceiver::flaggedPointDrawn,
                     viewer,&Viewer::drawFlaggedPoint);
    QObject::connect(this,&SerialReceiver::screenCleared,
                     viewer,&Viewer::drawClearedScreen);
}

void SerialReceiver::decoder(std::vector<bool> message){
    bool connected;
    int x=0;
    int y=0;
    unsigned int expectedSize = 22;
    if (message.size()==expectedSize){
        if (message[0]==true){
            // qDebug()<<"Received: Drawing a point!";
            connected=message[1];
            //convert binary coordinate x into decimal
            for(int i=0; i<COORDINATE_BITS; i++){
                x=x+(((int)message[i+2] )*(pow(2,i)));
                y=y+(((int)message[i+2+COORDINATE_BITS])*(pow(2,i)));
            }
            // qDebug()<<x<<y<<connected;
            FlaggedQPoint p(x,y);
            p.isConnected = connected;
            flaggedPointDrawn(p);
        }
        else if (message[0]==false){
            // qDebug()<<"Received: clear screen";
            screenCleared();
        }
    } else {
        qDebug()<<"Unexpected message of size:"<<message.size();
    }
}
