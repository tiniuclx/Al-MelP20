#ifndef SERIALSENDER_H
#define SERIALSENDER_H
#include <QObject>

#include "flaggedqpoint.h"
#include "canvas.h"


class serialsender : public QObject
{

Q_OBJECT

public:
    //explicit serialsender(QWidget *parent = 0);
    serialsender(Canvas *targetCanvas);
    Canvas *canvas;

protected:

private:

public slots:
    void saveFlaggedPoint(FlaggedQPoint p);
    //void drawClearedScreen();
};

#endif // SERIALSENDER_H
