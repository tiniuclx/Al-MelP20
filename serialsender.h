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
    void sendMessage(std::vector<bool> message);
    void saveFlaggedPoint(FlaggedQPoint p);
    void clearScreen();
    std::vector<bool> decToBin(int decimal);

protected:
    std::vector<bool> serialization(bool instruction, bool connected, std::vector<bool> x, std::vector<bool>y);
    Canvas *canvas;
    SerialReceiver *receiver;
};

#endif // SERIALSENDER_H
