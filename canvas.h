#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <vector>
#include <QPoint>
#include "flaggedqpoint.h"

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
    std::vector<FlaggedQPoint> *pointVector;

signals:

public slots:

};

#endif // CANVAS_H
