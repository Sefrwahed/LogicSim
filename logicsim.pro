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
    src/canvas.cpp \
    src/canvasmanager.cpp \
    src/componentstab.cpp \
    src/graphicgate.cpp \
    src/abstractgate.cpp \
    src/gates.cpp \
    src/gateparts.cpp

HEADERS += src/mainwindow.h \
    src/node.h \
    src/canvas.h \
    src/componentstab.h \
    src/canvasmanager.h \
    src/logicsim_global.h \
    src/graphicgate.h \
    src/abstractgate.h \
    src/gates.h \
    src/gateparts.h

FORMS += src/mainwindow.ui

RESOURCES += \
    logicsim.qrc
