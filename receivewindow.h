#ifndef RECEIVEWINDOW_H
#define RECEIVEWINDOW_H

#include <QMainWindow>
#include "canvas.h"
#include "viewer.h"

// ReceiveWindow is the wrapper around the Viewer class. It should
// contain functionality related to setting up the transmission, if
// any will be needed. The Viewer class should contain all the nece-
// ssary code to receive and view information sent from a Canvas class.
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
