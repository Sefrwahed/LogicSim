#include "mainwindow.h"

// Qt includes
#include <QApplication>
#include <QGuiApplication>

using namespace Logicsim;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
