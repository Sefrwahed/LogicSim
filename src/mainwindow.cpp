#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    ui->tableWidget->verticalHeader()->setVisible(false);
//    ui->tableWidget->horizontalHeader()->setVisible(false);
//    ui->tableWidget->setRowCount(10);
//    ui->tableWidget->setColumnCount(2);
//    ui->tableWidget->setShowGrid(true);
//    ui->tableWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

   QPixmap pix1("e.qrc:/and.png");   // and
    ui->label_and->setPixmap(pix1);
   // ui->label_and->setDragEnabled(true);

   QPixmap pix2 ("e.qrc:/nand.png");  //nand
    ui->label_nand->setPixmap(pix2);
    //ui->label_nand->setDragEnabled(true);

   QPixmap pix3("e.qrc:/or.png");  //or
    ui->label_or->setPixmap(pix3);
    //ui->label_or->setDragEnabled(true);

   QPixmap pix4("e.qrc:/nor.png");  //nor
    ui->label_nor->setPixmap(pix4);
    //ui->label_nor->setDragEnabled(true);

   QPixmap pix5("e.qrc:/xor.png");  //xor
    ui->label_xor->setPixmap(pix5);
    //ui->label_xor->setDragEnabled(true);

   QPixmap pix6("e.qrc:/xnor.png");  //xnor
    ui->label_xnor->setPixmap(pix6);
   // ui->label_xnor->setDragEnabled(true);

   QPixmap pix7("e.qrc:/not.png");  //not
    ui->label_not->setPixmap(pix7);
   // ui->label_not->setDragEnabled(true);






    // ui->tableWidget->setItem(0,0,item1);
   //QTableWidgetItem* item1 = new QTableWidgetItem(pix);
   //ui->tableWidget->setSelectionBehavior(QAbstracts);

      //ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->tableWidget->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}
