#include "viewer.h"

Viewer::Viewer(QWidget *parent) :
    QWidget(parent)
{
    this->setMinimumSize(400,300);
    pointVector = new std::vector<FlaggedQPoint>;
}
