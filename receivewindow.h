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
    Viewer *viewer;
private:

signals:

public slots:

};

#endif // RECEIVEWINDOW_H
