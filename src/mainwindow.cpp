#include "mainwindow.h"

// Qt includes

#include <QDebug>

// Local includes

#include "logicsim_global.h"
#include "ui_mainwindow.h"
#include "canvas.h"
#include "gates.h"

namespace Logicsim
{

/* Maximum tabs to be created in the main frame */
const int MAX_TAB_COUNT = 10;

class MainWindow::Private
{
public:
    Private() :
        tabsCount(0),
        tabWidget(0),
        compTab(0)
    {}

    int            tabsCount;
    QTabWidget*    tabWidget;
    ComponentsTab* compTab;
    QList<Canvas*> canvases;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), d(new Private)
{
    ui->setupUi(this);

    initComponentsTab();

    d->tabWidget = new QTabWidget(ui->frame);
    setMainFrameDisabled(true);
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
    d->compTab = new ComponentsTab();
    ui->gridLayout_3->addWidget(d->compTab);
}

void MainWindow::setMainFrameDisabled(bool disabled)
{
    if(disabled)
    {
        ui->frame->setStyleSheet("background-color: #D3D3D3");
        d->compTab->setDisabled(true);
    }
    else
    {
        ui->frame->setStyleSheet("");
        d->compTab->setDisabled(false);
    }
}

void MainWindow::newFile()
{
    if(d->tabsCount >= MAX_TAB_COUNT) return;
    Canvas* c = new Canvas(d->tabWidget);
    d->tabsCount++;
    int tabIndex = d->tabWidget->addTab(c->view(), "New Circuit");
    c->setTabIndex(tabIndex);
    d->canvases << c;
    setMainFrameDisabled(false);
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
    setMainFrameDisabled(!--d->tabsCount);
}

} // namespace Logicsim
