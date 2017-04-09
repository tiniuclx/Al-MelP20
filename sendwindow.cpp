#include "sendwindow.h"

SendWindow::SendWindow(QWidget *parent) :
    QMainWindow(parent)
{
    canvas = new Canvas;
    this->setCentralWidget(this->canvas);
    this->setWindowTitle("AlMel Send");
}
