#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
  //  ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setDragEnabled(true);
    QPixmap gatePixmap[GATES_TYPES_NUMBER];
    QIcon gateIcon[GATES_TYPES_NUMBER];
    QTableWidgetItem* gateItem[GATES_TYPES_NUMBER];
    gatePixmap[0] = QPixmap(":/gates/assets/gates/and.png");
    gatePixmap[1] = QPixmap(":/gates/assets/gates/nand.png");
    gatePixmap[2] = QPixmap(":/gates/assets/gates/nor.png");
    gatePixmap[3] = QPixmap(":/gates/assets/gates/not.png");
    gatePixmap[4] = QPixmap(":/gates/assets/gates/or.png");
    gatePixmap[5] = QPixmap(":/gates/assets/gates/xnor.png");
    gatePixmap[6] = QPixmap(":/gates/assets/gates/xor.png");

    for(int i = 0; i < GATES_TYPES_NUMBER; i++)
    {
        gateIcon[i] = QIcon(gatePixmap[i]);
        gateItem[i] = new QTableWidgetItem(gateIcon[i], "");
    }
    for(int item_no = 0; item_no < GATES_TYPES_NUMBER; item_no += 2)
    {
        ui->tableWidget->setItem(item_no/2, 0, gateItem[item_no]);
    }
    for(int item_no = 1; item_no < GATES_TYPES_NUMBER; item_no += 2)
    {
        ui->tableWidget->setItem(item_no/2, 1, gateItem[item_no]);
    }


    // ui->tableWidget->setItem(0,0,item1);
   //QTableWidgetItem* item1 = new QTableWidgetItem(pix);
   //ui->tableWidget->setSelectionBehavior(QAbstracts);


    //ui->tableWidget->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}
