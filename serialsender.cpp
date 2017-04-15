#include "serialsender.h"
#include <QDebug>
#include <vector>
#include <math.h>

#define COORDINATE_BITS 16


serialsender::serialsender(Canvas *targetCanvas, serialReceiver *targetSerialReceiver)
{
    receiver=targetSerialReceiver;
    canvas=targetCanvas;
    connect(canvas,&Canvas::flaggedPointDrawn,this,&serialsender::saveFlaggedPoint);
    connect(canvas,&Canvas::screenCleared,this,&serialsender::clearScreen);
}


// Receive a drawn point, store it in memory
void serialsender::saveFlaggedPoint(FlaggedQPoint p){

    std::vector<bool>vectx;
    std::vector<bool>vecty;
    std::vector<bool>drawInformation;

    //prints x coordinate, y coordinate and whether
    //the point is connected to the previous point
    //for each flaggedqpoint sent with the signal
    qDebug() << p.x() << p.y() << p.isConnected;

    //converts the x and y coordinates into binary
    //and stores them in vectors
    vectx=decToBin(p.x());
    vecty=decToBin(p.y());

    //Sends the information about which points to draw
    //When first argument is 1 the instruction is draw
    drawInformation=serialization(1,p.isConnected,vectx,vecty);
    sendMessage(drawInformation);

}

std::vector<bool>serialsender::decToBin(int decimal){
//converts decimal number into a binary number of size COORDINATE_BITS

    std::vector<bool>binary;

    while(decimal!=0){
        bool remainder=(decimal%2==0 ? 0:1);
        binary.push_back(remainder);
        decimal/=2;
    }

    //adds zeros to binary number to make sure it is the required length
    for(uint i=binary.size();i<COORDINATE_BITS;i++){
        binary.push_back(0);
    }return binary;
}

void serialsender::clearScreen(){
     //qDebug()<<"Cleared";

    std::vector<bool>clearInformation;
    std::vector<bool>dummyX;
    std::vector<bool>dummyY;

    //Sends the information for screen to be cleared
    //When first argument is 0 the instruction is clear
    //doesn't matter what the last two arguments are
    clearInformation=serialization(0,0,dummyX,dummyY);
    sendMessage(clearInformation);
}

std::vector<bool> serialsender::serialization(bool instruction, bool connected, std::vector<bool> x, std::vector<bool>y){

    std::vector<bool> information;
    //final structure of information vector:
    //information[0]=instruction
    //instruction=0 to clear, instruction=1 to draw
    //information[1]=isConnected
    //information[2:17]=binary x coordinate
    //information[18:33]=binary y coordinate




    //puts binary version of coordinates
    //in information vector
    //starting from most significant bit
    for(int i=0; i<COORDINATE_BITS; i++){
    information.push_back(y[i]);
    }

    for(int i=0; i<COORDINATE_BITS; i++){
    information.push_back(x[i]);
    }

    //used to make sure the coordinates are
    //being converted to binary correctly
    int testx;
    for(int i=0; i<COORDINATE_BITS; i++){
        testx=testx+(((int)x[i])*(pow(2,i)));
    }
    //qDebug()<<testx;


    information.push_back(connected);
    information.push_back(instruction);

    return information;
}

void serialsender::sendMessage(std::vector<bool> message){
    receiver->decoder(message);
}
