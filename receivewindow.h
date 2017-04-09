#ifndef RECEIVEWINDOW_H
#define RECEIVEWINDOW_H

#include <QMainWindow>
#include "canvas.h"
#include "viewer.h"

class ReceiveWindow : public QMainWindow
{
    Q_OBJECT
public:
    ReceiveWindow(QWidget *parent = 0);
private:
    Viewer *viewer;
signals:

public slots:

};

#endif // RECEIVEWINDOW_H
