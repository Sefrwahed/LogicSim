#include "mainwindow.h"

// Qt includes
#include <QDebug>

// Local includes
#include "ui_mainwindow.h"
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
    ComponentsTab* components = new ComponentsTab();
    ui->gridLayout_3->addWidget(components);
}

void MainWindow::setMainFrameDisabled(bool disabled)
{
    if(disabled)
    {
        ui->frame->setStyleSheet("background-color: #D3D3D3");
    }
    else
    {
        ui->frame->setStyleSheet("");
    }
}

void MainWindow::newFile()
{
    if(d->tabsCount >= 10) return;
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
