#-------------------------------------------------
#
# Project created by QtCreator 2015-02-04T13:43:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab20
TEMPLATE = app


SOURCES += main.cpp\
    sendwindow.cpp \
    receivewindow.cpp \
    canvas.cpp \
    viewer.cpp \
    serialreceiver.cpp \
    serialsender.cpp \
    threadsafequeue.cpp

HEADERS  += \
    sendwindow.h \
    receivewindow.h \
    canvas.h \
    viewer.h \
    flaggedqpoint.h \
    serialreceiver.h \
    serialsender.h \
    threadsafequeue.h

FORMS    +=

LIBS += -L/usr/local/lib -lwiringPi -lpthread
