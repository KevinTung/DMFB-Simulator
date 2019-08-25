#-------------------------------------------------
#
# Project created by QtCreator 2019-08-20T20:25:10
#
#-------------------------------------------------

QT       += core gui
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 7thQTapp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    initwindow.cpp \
    frame.cpp \
    wash.cpp

HEADERS  += mainwindow.h \
    initwindow.h \
    frame.h \
    wash.h

FORMS    += mainwindow.ui \
    initwindow.ui
