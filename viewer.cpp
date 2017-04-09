#include "viewer.h"

Viewer::Viewer(QWidget *parent) :
    QWidget(parent)
{
    this->setMinimumSize(400,300);
    pointVector = new std::vector<FlaggedQPoint>;
}

void Viewer::drawFlaggedPoint(FlaggedQPoint p){
    pointVector->push_back(p);
    update();
}

void Viewer::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen pen(Qt::black);
    pen.setWidth(3);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);

    for(unsigned i=1;i<pointVector->size();i++){
        if((*pointVector)[i].isConnected){
            QLine line((*pointVector)[i],(*pointVector)[i-1]);
            painter.drawLine(line);
        }
    }
}
