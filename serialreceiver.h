#ifndef SERIALRECEIVER_H
#define SERIALRECEIVER_H

#include <vector>
#include <QObject>
#include "flaggedqpoint.h"
#include "viewer.h"

class SerialReceiver : public QObject
{
    Q_OBJECT
public:
    void decoder(std::vector<bool> message);
protected:
    SerialReceiver(Viewer *viewer);
signals:
    void flaggedPointDrawn(FlaggedQPoint p);
    void screenCleared();

};

#endif // SERIALRECEIVER_H
