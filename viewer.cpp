#include "viewer.h"
#include <QStyleOption>

Viewer::Viewer(QWidget *parent) :
    QWidget(parent)
{
    this->setMinimumSize(600,400);
    pointVector = new std::vector<FlaggedQPoint>;
    // Makes the background white
    this->setStyleSheet(tr("background-color:white;"));
}

// Receive a drawn point, store it in memory and update
// the screen
void Viewer::drawFlaggedPoint(FlaggedQPoint p){
    pointVector->push_back(p);
    update();
}

// Paint everything stored in memory whenever update() is called.
void Viewer::paintEvent(QPaintEvent *event){
    // Properties of the lines being drawn. As of yet hard-
    // coded, should be easy to extend functionality to change
    // these parameters.
    QPainter painter(this);
    QPen pen(Qt::black);
    pen.setWidth(3);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);
    // Boilerplate to draw a white background
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&painter,this);

    // For every point in pointVector
    for(unsigned i=1;i<pointVector->size();i++){
        if((*pointVector)[i].isConnected){
            // Draw a line between the point and the previous one
            // if they are meant to be connected.
            QLine line((*pointVector)[i],(*pointVector)[i-1]);
            painter.drawLine(line);
        }
    }
}

// Erases the data in pointVector, thus clearing the screen.
void Viewer::drawClearedScreen(){
    pointVector->clear();
    update();
}
