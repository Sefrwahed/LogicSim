#include "mainwindow.h"
#include <QApplication>
#include <qdebug.h>
#include "gate.h"

using namespace Logicsim;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
