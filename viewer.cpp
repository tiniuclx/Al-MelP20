#include "viewer.h"
#include <QStyleOption>

Viewer::Viewer(QWidget *parent) :
    QWidget(parent)
{
    this->setMinimumSize(600,400);
    pointVector = new std::vector<FlaggedQPoint>;    
    this->setStyleSheet(tr("background-color:white;"));
}

// Receive a drawn point from Canvas, store it in memory
// and update the screen
void Viewer::drawFlaggedPoint(FlaggedQPoint p){
    pointVector->push_back(p);
    update();
}
// Identical to Canvas::paintEvent
void Viewer::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen pen(Qt::black);
    pen.setWidth(3);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);
    // Boilerplate to draw a white background
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&painter,this);

    for(unsigned i=1;i<pointVector->size();i++){
        if((*pointVector)[i].isConnected){
            QLine line((*pointVector)[i],(*pointVector)[i-1]);
            painter.drawLine(line);
        }
    }
}

void Viewer::drawClearedScreen(){
    pointVector->clear();
    update();
}
