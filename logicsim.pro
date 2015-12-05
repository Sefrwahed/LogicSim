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
    src/node.cpp \
    src/gate.cpp\
    src/drawablegenericgate.cpp \
    src/canvas.cpp \
    src/componentstab.cpp \
    src/inputoutputcomponents.cpp

HEADERS += src/mainwindow.h \
    src/node.h \
    src/gate.h \
    src/drawablegenericgate.h \
    src/canvas.h \
    src/componentstab.h \
    src/inputoutputcomponents.h

FORMS += src/mainwindow.ui

RESOURCES += \
    logicsim.qrc
