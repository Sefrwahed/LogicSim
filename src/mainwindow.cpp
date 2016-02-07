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
    WorkspaceTab* workspaceTab;
    QList<Canvas*> canvases;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), d(new Private)
{
    ui->setupUi(this);

    initComponentsTab();
    initWorkspaceTab();

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
    disconnect(d->tabWidget, SIGNAL(currentChanged(int)),
               this, SLOT(changeManager(int)));
    disconnect(d->tabWidget, SIGNAL(currentChanged(int)),
               d->workspaceTab, SLOT(updateGates()));
    disconnect(this, SIGNAL(notLastTabClosed(int)),
               this, SLOT(changeManager(int)));
    disconnect(this, SIGNAL(notLastTabClosed(int)),
               d->workspaceTab, SLOT(updateGates()));
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

void MainWindow::initWorkspaceTab()
{
    d->workspaceTab = new WorkspaceTab();
    ui->gridLayout_3->addWidget(d->workspaceTab);
}

void MainWindow::setMainFrameDisabled(bool disabled)
{
    if(disabled)
    {
        ui->frame->setStyleSheet("background-color: #D3D3D3");
        d->compTab->setDisabled(true);
        d->workspaceTab->setDisabled(true);
        d->workspaceTab->clear();
    }
    else
    {
        ui->frame->setStyleSheet("");
        d->compTab->setDisabled(false);
        d->workspaceTab->setDisabled(false);
    }
}

void MainWindow::newFile()
{
    if(d->tabsCount >= MAX_TAB_COUNT) return;

    Canvas* c = new Canvas(d->tabWidget);
    d->canvases << c;
    if(d->tabsCount == 0)
    {
        connect(d->tabWidget, SIGNAL(currentChanged(int)),
                this, SLOT(changeManager(int)));
        connect(d->tabWidget, SIGNAL(currentChanged(int)),
                d->workspaceTab, SLOT(updateGates()));
        connect(this, SIGNAL(notLastTabClosed(int)),
                this, SLOT(changeManager(int)));
        connect(this, SIGNAL(notLastTabClosed(int)),
                d->workspaceTab, SLOT(updateGates()));
    }
    d->tabsCount++;
    int tabIndex = d->tabWidget->addTab(c->view(), "New Circuit");
    c->setTabIndex(tabIndex);
    setMainFrameDisabled(false);
}

void MainWindow::closeTab(int tabIndex)
{
    qDebug() << "Tab is closing: " << tabIndex;

    int tmp = tabIndex;
    if(d->canvases.length() == 1)
    {
        disconnect(d->tabWidget, SIGNAL(currentChanged(int)),
                   this, SLOT(changeManager(int)));
        disconnect(d->tabWidget, SIGNAL(currentChanged(int)),
                   d->workspaceTab, SLOT(updateGates()));
        disconnect(this, SIGNAL(notLastTabClosed(int)),
                   this, SLOT(changeManager(int)));
        disconnect(this, SIGNAL(notLastTabClosed(int)),
                   d->workspaceTab, SLOT(updateGates()));

    }
    d->tabWidget->removeTab(tabIndex);

    for (int i = tabIndex+1; i < d->canvases.length(); ++i)
    {
        d->canvases.at(i)->setTabIndex(tmp++);
    }
    delete d->canvases.at(tabIndex);
    d->canvases.removeAt(tabIndex);
    if(tabIndex < d->tabsCount - 1)
    {
        emit notLastTabClosed(tabIndex);
    }
    setMainFrameDisabled(!--d->tabsCount);
}

void MainWindow::changeManager(int index)
{
    d->workspaceTab->setManager(d->canvases.at(index)->getCanvasManager());
}

} // namespace Logicsim
