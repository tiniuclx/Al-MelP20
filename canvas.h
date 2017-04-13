#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <vector>
#include <QPoint>
#include "flaggedqpoint.h"
#include "viewer.h"

// The Canvas widged is where the user actually draws their picture.
// It should contain the code neccessary to draw things, as well as
// transmit them to an instance of Viewer. The connection between the
// two will probably be made in the main() loop of the program.

// The Canvas class inherits the screen drawing functionality from
// Viewer, adds mouse interaction functionality (e.g. drawing
// when the widget is clicked, clearing the screen) and is also
// able to communicate with an instance of Viewer
class Canvas : public Viewer
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = 0);
protected:
    void mouseReleaseEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
private:

signals:
    void flaggedPointDrawn(FlaggedQPoint p);
    void screenCleared();
public slots:
    void drawClearedScreen();
};

#endif // CANVAS_H
