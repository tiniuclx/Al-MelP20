#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <vector>
#include <QPoint>

class FlaggedQPoint : public QPoint
{
public:
    bool isConnected;
    FlaggedQPoint(){
        isConnected=true;
    }
    FlaggedQPoint(int x, int y){
        isConnected=true;
        setX(x);
        setY(y);
    }
};

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
