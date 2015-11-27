#include "mainwindow.h"
#include <QApplication>
#include <qdebug.h>
#include "gate.h"

using namespace Logicsim;

int main(int argc, char *argv[])
{
    /*
    NotGate b;
    //b.setMaxInput(2);
    QList<Node*> n;

    Node* m;
    m->setValue(false);
    n.append(m);
    b.setInput(n);
    b.calcOutput();
    bool c = (b.outputNode())->getValue();


    qDebug() << c;*/
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
