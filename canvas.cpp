#include "canvas.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QLine>

Canvas::Canvas(QWidget *parent) :
    QWidget(parent)
{
    this->setMinimumSize(400,300);
    pointVector = new std::vector<FlaggedQPoint>;
}

void Canvas::paintEvent(QPaintEvent *event){
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

void Canvas::mouseReleaseEvent(QMouseEvent *event){
    int mouseX = event->x();
    int mouseY = event->y();
    FlaggedQPoint p(mouseX,mouseY);
    pointVector->push_back(p);
    emit flaggedPointDrawn(p);
    update();
}

void Canvas::mousePressEvent(QMouseEvent *event){
    int mouseX = event->x();
    int mouseY = event->y();
    FlaggedQPoint p(mouseX,mouseY);
    p.isConnected = false;
    pointVector->push_back(p);
    emit flaggedPointDrawn(p);
    update();
}

void Canvas::mouseMoveEvent(QMouseEvent *event){
    int mouseX = event->x();
    int mouseY = event->y();
    FlaggedQPoint p(mouseX,mouseY);
    pointVector->push_back(p);
    emit flaggedPointDrawn(p);
    update();
}
