#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include "flaggedqpoint.h"

// Viewer functionality mirrors canvas functionality almost completely.
// Consider refactoring the two so they share an ancestor?
class Viewer : public QWidget
{
    Q_OBJECT
public:
    explicit Viewer(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent * event);
private:
    std::vector<FlaggedQPoint> *pointVector;

signals:

public slots:
    void drawFlaggedPoint(FlaggedQPoint p);

};

#endif // VIEWER_H
