#include "canvas.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QLine>


Canvas::Canvas(QWidget *parent) :
    QWidget(parent)
{
    this->setMinimumSize(400,300);
    pointVector = new std::vector<QPoint>;
}

void Canvas::paintEvent(QPaintEvent *event){

    QPainter painter(this);
    QPen pen(Qt::black);
    pen.setWidth(3);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);

    for(unsigned i=1;i<pointVector->size();i++){
        QLine line((*pointVector)[i],(*pointVector)[i-1]);
        painter.drawLine(line);
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event){
    int mouseX = event->x();
    int mouseY = event->y();
    pointVector->push_back(QPoint(mouseX,mouseY));
    update();
}

void Canvas::mousePressEvent(QMouseEvent *event){
    int mouseX = event->x();
    int mouseY = event->y();
    pointVector->push_back(QPoint(mouseX,mouseY));
    update();
}

void Canvas::mouseMoveEvent(QMouseEvent *event){
    int mouseX = event->x();
    int mouseY = event->y();
    pointVector->push_back(QPoint(mouseX,mouseY));
    update();
}
