#include "sendwindow.h"
#include <QDebug>
#include <QAction>

SendWindow::SendWindow(QWidget *parent) :
    QMainWindow(parent)
{
    canvas = new Canvas;
    // The central widget of a QMainWindow represents the core
    // functionality of the program, around which the user in-
    // terface is built.
    this->setCentralWidget(this->canvas);
    this->setWindowTitle("AlMel Send");

    toolbar = this->addToolBar(tr("Tools"));
    toolbar->addAction(tr("Clear"));

    connect(toolbar,&QToolBar::actionTriggered,this,&SendWindow::handleToolbar);
    connect(this,&SendWindow::clearScreen,canvas,&Canvas::drawClearedScreen);
}

void SendWindow::handleToolbar(QAction* action){
    if(action->text()==tr("Clear"))
        emit clearScreen();
    else
        qDebug()<<"Unknown action:"<<action->text();
}


