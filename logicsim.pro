#-------------------------------------------------
#
# Project created by QtCreator 2015-10-28T21:54:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = logicsim
TEMPLATE = app

SOURCES += src/main.cpp \
           src/mainwindow.cpp \
    src/drawablegenericgate.cpp

HEADERS += src/mainwindow.h \
    src/drawablegenericgate.h

FORMS += src/mainwindow.ui
