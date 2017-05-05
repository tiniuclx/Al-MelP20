#include "serialsender.h"
#include <QDebug>
#include <vector>
#include <math.h>

const int COORDINATE_BITS = 10;


SerialSender::SerialSender(Canvas *targetCanvas, SerialReceiver *targetSerialReceiver, ThreadSafeQueue *targetQueue)
{
    receiver=targetSerialReceiver;
    canvas=targetCanvas;
    connect(canvas,&Canvas::flaggedPointDrawn,this,&SerialSender::saveFlaggedPoint);
    connect(canvas,&Canvas::screenCleared,this,&SerialSender::clearScreen);

    send_queue = targetQueue;
}


// Receive a drawn point, store it in memory
void SerialSender::saveFlaggedPoint(FlaggedQPoint p){
    // qDebug()<<"Sending point:";
    // initialises the vectors with COORDINATE_BITS zeroes
    std::vector<bool>vectx;
    std::vector<bool>vecty;
    std::vector<bool>drawInformation;

    //prints x coordinate, y coordinate and whether
    //the point is connected to the previous point
    //for each flaggedqpoint sent with the signal
    // qDebug() << p.x() << p.y() << p.isConnected;

    //converts the x and y coordinates into binary
    //and stores them in vectors
    vectx=decToBin(p.x());
    vecty=decToBin(p.y());

    //Sends the information about which points to draw
    //When first argument is 1 the instruction is draw
    drawInformation=serialization(1,p.isConnected,vectx,vecty);
    sendMessage(drawInformation);
}

// first bit is LSB => stored LSB:MSB
std::vector<bool>SerialSender::decToBin(int decimal){
    std::vector<bool>binary;

    while(decimal!=0){
        bool remainder=(decimal%2==0 ? 0:1);
        binary.push_back(remainder);
        decimal/=2;
    }

    //adds zeros to binary number to make sure it is the required length
    for(uint i=binary.size();i<COORDINATE_BITS;i++){
        binary.push_back(0);
    }
    return binary;
}

void SerialSender::clearScreen(){
     qDebug()<<"Sending: Clear Screen!";

    std::vector<bool>clearInformation;
    std::vector<bool>dummyX(COORDINATE_BITS,0);
    std::vector<bool>dummyY(COORDINATE_BITS,0);

    //Sends the information for screen to be cleared
    //When first argument is 0 the instruction is clear
    //doesn't matter what the last two arguments are
    clearInformation=serialization(0,0,dummyX,dummyY);
    sendMessage(clearInformation);
}

std::vector<bool> SerialSender::serialization(bool instruction, bool connected, std::vector<bool> x, std::vector<bool>y){
    std::vector<bool> information;
    //final structure of information vector:
    //information[0]=instruction
    //instruction=0 to clear, instruction=1 to draw
    //information[1]=isConnected
    //information[2:11] =binary x coordinate, LSB:MSB
    //information[12:21]=binary y coordinate, LSB:MSB

    //puts binary version of coordinates
    //in information vector
    //starting from most significant bit
    information.push_back(instruction);
    information.push_back(connected);

    information.insert(information.end(),x.begin(),x.end());
    information.insert(information.end(),y.begin(),y.end());
    return information;
}

void SerialSender::sendMessage(std::vector<bool> message){
    send_queue->push(message);
}

int SerialSender::messageSize(){
    // Command bit (draw or clear), isConnected flag,
    // X and Y coordinate.
    return (2 + COORDINATE_BITS * 2);
}
