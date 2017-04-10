#ifndef SENDWINDOW_H
#define SENDWINDOW_H

#include <QMainWindow>
#include "canvas.h"

// The SendWindow class represents the UI wrapper around Canvas.
// It should contain all the necessary functionality to signal
// drawing tool changes, color changes and other features.
// The actual drawing is handled by the Canvas class.

// Because SendWindow inherits from QMainWindow, it is easy to
// add menu bars and toolboxes: see QMainWindow documentation.
class SendWindow : public QMainWindow
{
    Q_OBJECT
public:
    SendWindow(QWidget *parent = 0);
    Canvas *canvas;
protected:

private:
signals:

public slots:

};

#endif // SENDWINDOW_H
