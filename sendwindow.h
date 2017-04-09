#ifndef SENDWINDOW_H
#define SENDWINDOW_H

#include <QMainWindow>
#include "canvas.h"

class SendWindow : public QMainWindow
{
    Q_OBJECT
public:
    SendWindow(QWidget *parent = 0);
protected:

private:
    Canvas *canvas;
signals:

public slots:

};

#endif // SENDWINDOW_H
