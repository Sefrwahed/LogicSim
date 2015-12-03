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
    src/drawablegenericgate.cpp

HEADERS += src/mainwindow.h \
    src/node.h \
    src/gate.h \
    src/drawablegenericgate.h

FORMS += src/mainwindow.ui

DISTFILES += \
    ../../../../Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x64/GlU32.Lib

<<<<<<< HEAD
RESOURCES += \
    myres.qrc
=======
FORMS += src/mainwindow.ui

RESOURCES += \
    src/resources.qrc
>>>>>>> LS7
