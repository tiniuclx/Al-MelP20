#include "sendwindow.h"

SendWindow::SendWindow(QWidget *parent) :
    QMainWindow(parent)
{
    canvas = new Canvas;
    // The central widget of a QMainWindow represents the core
    // functionality of the program, around which the user in-
    // terface is built.
    this->setCentralWidget(this->canvas);
    this->setWindowTitle("AlMel Send");
}
