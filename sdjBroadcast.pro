#-------------------------------------------------
#
# Project created by QtCreator 2013-10-30T01:39:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sdjBroadcast
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    bcastsettings.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    bcastsettings.h

FORMS    += mainwindow.ui \
    dialog.ui
