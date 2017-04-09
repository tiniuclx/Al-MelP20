#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include "flaggedqpoint.h"

class Viewer : public QWidget
{
    Q_OBJECT
public:
    explicit Viewer(QWidget *parent = 0);
private:
    std::vector<FlaggedQPoint> *pointVector;

signals:

public slots:

};

#endif // VIEWER_H
