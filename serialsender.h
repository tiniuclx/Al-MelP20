#ifndef SERIALSENDER_H
#define SERIALSENDER_H

#include "flaggedqpoint.h"
#include "canvas.h"


class serialsender
{

Q_OBJECT

public:
    //explicit serialsender(QWidget *parent = 0);
    serialsender();
    Canvas *canvas;

private:

public slots:
    void saveFlaggedPoint(FlaggedQPoint p);
    //void drawClearedScreen();
};

#endif // SERIALSENDER_H
