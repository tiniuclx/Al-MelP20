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
// Paint everything stored in memory whenever update() is called.
void Canvas::paintEvent(QPaintEvent *event){
    // Properties of the lines being drawn. As of yet hard-
    // coded, should be easy to extend functionality to change
    // these parameters.
    QPainter painter(this);
    QPen pen(Qt::black);
    pen.setWidth(3);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);
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

// Draw a point whenever you release the mouse. Might
// be superflous
void Canvas::mouseReleaseEvent(QMouseEvent *event){

    int mouseX = event->x();
    int mouseY = event->y();
    FlaggedQPoint p(mouseX,mouseY);
    pointVector->push_back(p);
    // Tell an instance of Viewer that a flagged point was drawn
    emit flaggedPointDrawn(p);
    update();
}

// Draw a point whenever you click the mouse
void Canvas::mousePressEvent(QMouseEvent *event){
    int mouseX = event->x();
    int mouseY = event->y();
    FlaggedQPoint p(mouseX,mouseY);
    // After you let go and click again, the drawings,
    // and therefore the points, shouldnt be connected.
    p.isConnected = false;
    pointVector->push_back(p);
    // Tell an instance of Viewer that a flagged point was drawn
    emit flaggedPointDrawn(p);
    update();
}

// Whenever the mouse is moved, draw a point at the cursor
// location. By default, Qt only tracks mouse movements when
// one of the mouse buttons is held down, therefore no logic
// is needed to check for that.
void Canvas::mouseMoveEvent(QMouseEvent *event){
    int mouseX = event->x();
    int mouseY = event->y();
    FlaggedQPoint p(mouseX,mouseY);
    pointVector->push_back(p);
    // Tell an instance of Viewer that a flagged point was drawn
    emit flaggedPointDrawn(p);
    update();
}
