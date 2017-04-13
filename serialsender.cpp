#include "serialsender.h"
#include <QDebug>

serialsender::serialsender()
{
     //connect(this,&serialsender::saveFlaggedPoint,canvas,&Canvas::flaggedPointDrawn);
}


// Receive a drawn point, store it in memory
void serialsender::saveFlaggedPoint(FlaggedQPoint p){
    //qdebug()<<
}

