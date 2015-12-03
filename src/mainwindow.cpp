#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);

    if(GATES_TYPES_NUMBER % 2 != 0)
        ui->tableWidget->setRowCount(GATES_TYPES_NUMBER/2 + 1);
    else
        ui->tableWidget->setRowCount(GATES_TYPES_NUMBER/2);

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setShowGrid(true);

    ui->tableWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    ui->tableWidget->setDragEnabled(true);

    QPixmap gatePixmap[GATES_TYPES_NUMBER];
    QLabel* gateItem[GATES_TYPES_NUMBER];
    gatePixmap[0] = QPixmap(":/gates/assets/gates/and.png");
    gatePixmap[1] = QPixmap(":/gates/assets/gates/nand.png");
    gatePixmap[2] = QPixmap(":/gates/assets/gates/nor.png");
    gatePixmap[3] = QPixmap(":/gates/assets/gates/not.png");
    gatePixmap[4] = QPixmap(":/gates/assets/gates/or.png");
    gatePixmap[5] = QPixmap(":/gates/assets/gates/xnor.png");
    gatePixmap[6] = QPixmap(":/gates/assets/gates/xor.png");

    for(int i = 0; i < GATES_TYPES_NUMBER; i++)
    {
        gateItem[i] = new QLabel();
        gateItem[i]->setPixmap(gatePixmap[i]);
    }
    for(int item_no = 0; item_no < GATES_TYPES_NUMBER; item_no += 2)
    {
        ui->tableWidget->setCellWidget(item_no/2, 0, gateItem[item_no]);
    }
    for(int item_no = 1; item_no < GATES_TYPES_NUMBER; item_no += 2)
    {
        ui->tableWidget->setCellWidget(item_no/2, 1, gateItem[item_no]);
    }

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MainWindow::~MainWindow()
{
    delete ui;
}
