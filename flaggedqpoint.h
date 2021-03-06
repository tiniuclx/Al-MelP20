#ifndef FLAGGEDQPOINT_H
#define FLAGGEDQPOINT_H
#include <QPoint>
#include <QMetaType>

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

Q_DECLARE_METATYPE(FlaggedQPoint)

#endif // FLAGGEDQPOINT_H
