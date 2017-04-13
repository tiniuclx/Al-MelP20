#ifndef FLAGGEDQPOINT_H
#define FLAGGEDQPOINT_H
#include <QPoint>

class FlaggedQPoint : public QPoint
{
public:
    bool isConnected;
    FlaggedQPoint(){
        isConnected=true;
    }
    FlaggedQPoint(int x, int y){
        isConnected=true;
        setX(x);
        setY(y);
    }
};

#endif // FLAGGEDQPOINT_H
