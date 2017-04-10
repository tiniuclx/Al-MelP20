#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <vector>
#include <QPoint>
#include "flaggedqpoint.h"

// The Canvas widged is where the user actually draws their picture.
// It should contain the code neccessary to draw things, as well as
// transmit them to an instance of Viewer. The connection between the
// two will probably be made in the main() loop of the program.
class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
private:
    // Vector containing what is currently on-screen. A clearWindow
    // method would clear the contents of this vector.
    std::vector<FlaggedQPoint> *pointVector;

signals:
    void flaggedPointDrawn(FlaggedQPoint p);
public slots:

};

#endif // CANVAS_H
