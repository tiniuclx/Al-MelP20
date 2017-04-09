#include "receivewindow.h"

ReceiveWindow::ReceiveWindow(QWidget *parent) :
    QMainWindow(parent)
{
    viewer = new Viewer;
    this->setCentralWidget(viewer);
    this->setWindowTitle("AlMel Receive");

}
