#ifndef SERIALSENDER_H
#define SERIALSENDER_H
#include <QObject>

#include "flaggedqpoint.h"
#include "canvas.h"
#include "serialreceiver.h"
#include <vector>


class SerialSender : public QObject
{

Q_OBJECT

public:
    SerialSender(Canvas *targetCanvas, SerialReceiver *targetSerialReceiver);
    Canvas *canvas;
    SerialReceiver *receiver;
    void sendMessage(std::vector<bool> message);

protected:
    std::vector<bool> serialization(bool instruction, bool connected, std::vector<bool> x, std::vector<bool>y);
    std::vector<bool> decToBin(int decimal);
public:
    void saveFlaggedPoint(FlaggedQPoint p);
    void clearScreen();
};

#endif // SERIALSENDER_H
