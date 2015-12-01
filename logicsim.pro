#-------------------------------------------------
#
# Project created by QtCreator 2015-10-28T21:54:36
#
#-------------------------------------------------

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_LFLAGS += /NODEFAULTLIB:MSVCRT?

TARGET = logicsim
TEMPLATE = app

SOURCES += src/main.cpp \
           src/mainwindow.cpp

HEADERS += src/mainwindow.h \
    src/componentstable.h

FORMS += src/mainwindow.ui

DISTFILES += \
    ../../../../Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x64/GlU32.Lib

RESOURCES += \
    src/e.qrc
