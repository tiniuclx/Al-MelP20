#include "serialsender.h"
#include <QDebug>


serialsender::serialsender(Canvas *targetCanvas)
{
    canvas=targetCanvas;
    connect(canvas,&Canvas::flaggedPointDrawn,this,&serialsender::saveFlaggedPoint);
}


// Receive a drawn point, store it in memory
void serialsender::saveFlaggedPoint(FlaggedQPoint p){
    //qDebug()<<"hi";

    qDebug() << p.x() << p.y() << p.isConnected;

}


