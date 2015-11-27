#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawablegenericgate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Logicsim::Gate *gate = new Logicsim::Gate();
    gate->setPos(0, 0);
    QGraphicsScene *sc=new QGraphicsScene();
    sc->addItem(gate);
    ui->graphicsView->setScene(sc);
}

MainWindow::~MainWindow()
{
    delete ui;
}
