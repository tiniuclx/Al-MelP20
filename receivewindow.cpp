#include "receivewindow.h"

ReceiveWindow::ReceiveWindow(QWidget *parent) :
    QMainWindow(parent)
{
    viewer = new Viewer;
    // The central widget of a QMainWindow represents the core
    // functionality of the program, around which the user in-
    // terface is built.
    this->setCentralWidget(viewer);
    this->setWindowTitle("AlMel Receive");
}
