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
    src/node.cpp

HEADERS += src/mainwindow.h \
    src/node.h

FORMS += src/mainwindow.ui
