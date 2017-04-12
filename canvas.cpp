#include "canvas.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QLine>
#include <QStyleOption>

// Inherit the constructor of Viewer
Canvas::Canvas(QWidget *parent) :
    Viewer(parent)
{
    // Deliberately left empty
}

// Draw a point whenever you release the mouse. Might
// be superflous
void Canvas::mouseReleaseEvent(QMouseEvent *event){
    int mouseX = event->x();
    int mouseY = event->y();
    FlaggedQPoint p(mouseX,mouseY);
    // Tell an instance of Viewer that a flagged point was drawn
    emit flaggedPointDrawn(p);
    this->drawFlaggedPoint(p);
}

// Draw a point whenever you click the mouse
void Canvas::mousePressEvent(QMouseEvent *event){
    int mouseX = event->x();
    int mouseY = event->y();
    FlaggedQPoint p(mouseX,mouseY);
    // After you let go and click again, the drawings,
    // and therefore the points, shouldnt be connected.
    p.isConnected = false;
    // Tell an instance of Viewer that a flagged point was drawn
    emit flaggedPointDrawn(p);
    this->drawFlaggedPoint(p);
}

// Whenever the mouse is moved, draw a point at the cursor
// location. By default, Qt only tracks mouse movements when
// one of the mouse buttons is held down, therefore no logic
// is needed to check for that.
void Canvas::mouseMoveEvent(QMouseEvent *event){
    int mouseX = event->x();
    int mouseY = event->y();
    FlaggedQPoint p(mouseX,mouseY);
    // Tell an instance of Viewer that a flagged point was drawn
    emit flaggedPointDrawn(p);
    this->drawFlaggedPoint(p);
}

// Clears the screen and signals that the class has been instructed
// to do so.
void Canvas::drawClearedScreen(){
    Viewer::drawClearedScreen();
    emit screenCleared();
}
