#include "mainwindow.h"
#include "ui_mainwindow.h"

// Qt includes
#include <QDebug>

// Local includes
#include "canvas.h"

namespace Logicsim
{

const int MAX_TABS_COUNT = 10;

class MainWindow::Private
{
public:
    Private() :
        tabsCount(0),
        tabWidget(0)
    {}

    int            tabsCount;
    QTabWidget*    tabWidget;
    QList<Canvas*> canvases;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), d(new Private)
{
    ui->setupUi(this);

    initComponentsTab();


    d->tabWidget = new QTabWidget(ui->frame);
    ui->frameGridLayout->addWidget(d->tabWidget);
    d->tabWidget->setTabsClosable(true);

    // Connection
    connect(ui->actionNew, SIGNAL(triggered(bool)),
            this, SLOT(newFile()));

    connect(d->tabWidget, SIGNAL(tabCloseRequested(int)),
            this, SLOT(closeTab(int)));

}

MainWindow::~MainWindow()
{
    delete ui;

    foreach (Canvas* c, d->canvases)
    {
        delete c;
    }

    delete d;
}


void MainWindow::initComponentsTab()
{
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);

    if(GATES_TYPES_NUMBER % 2 != 0)
        ui->tableWidget->setRowCount(GATES_TYPES_NUMBER/2 + 1);
    else
        ui->tableWidget->setRowCount(GATES_TYPES_NUMBER/2);

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setShowGrid(false);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

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

void MainWindow::newFile()
{
    if(d->tabsCount >= 10) return;
    Canvas* c = new Canvas(d->tabWidget);
    d->tabsCount++;
    int tabIndex = d->tabWidget->addTab(c->view(), "New File " + QString::number(d->tabsCount));
    c->setTabIndex(tabIndex);
    d->canvases << c;
}

void MainWindow::closeTab(int tabIndex)
{
    qDebug() << "Tab is closing: " << tabIndex;

    int tmp = tabIndex;


    d->tabWidget->removeTab(tabIndex);

    for (int i = tabIndex+1; i < d->canvases.length(); ++i)
    {
        d->canvases.at(i)->setTabIndex(tmp++);
    }

    delete d->canvases.at(tabIndex);
    d->canvases.removeAt(tabIndex);
    d->tabsCount--;
}

} // namespace Logicsim
