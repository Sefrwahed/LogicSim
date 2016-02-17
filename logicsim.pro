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
    src/inputoutputcomponents.cpp \
    src/gate.cpp \
    src/gates.cpp \
    src/connectionline.cpp \
    src/workspacetab.cpp \
    src/inouparts.cpp \
    src/component.cpp \
    src/pin.cpp

HEADERS += src/mainwindow.h \
    src/node.h \
    src/canvas.h \
    src/componentstab.h \
    src/inputoutputcomponents.h \
    src/canvasmanager.h \
    src/logicsim_global.h \
    src/gate.h \
    src/connectionline.h \
    src/gates.h \
    src/workspacetab.h \
    src/inouparts.h \
    src/component.h \
    src/pin.h

FORMS += src/mainwindow.ui

RESOURCES += \
    logicsim.qrc
