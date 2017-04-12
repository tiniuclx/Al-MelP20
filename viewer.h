#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include "flaggedqpoint.h"

// The Viewer class contains the functionality necessary
// to display user-drawn schematics
class Viewer : public QWidget
{
    Q_OBJECT
public:
    explicit Viewer(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent * event);
    // Vector containing what is currently on-screen.
    std::vector<FlaggedQPoint> *pointVector;
private:

signals:

public slots:
    void drawFlaggedPoint(FlaggedQPoint p);
    void drawClearedScreen();

};

#endif // VIEWER_H
