#include "mainwindow.h"
#include "ui_mainwindow.h"

// Qt includes
#include <QDebug>

// Local includes
#include "canvas.h"

namespace Logicsim
{

class MainWindow::Private
{
public:
    Private() :
        tabWidget(0)
    {}

    QTabWidget*         tabWidget;
    QHash<int, Canvas*> canvases;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), d(new Private)
{
    ui->setupUi(this);

    d->tabWidget = new QTabWidget(ui->frame);
    ui->frameGridLayout->addWidget(d->tabWidget);
    d->tabWidget->setTabsClosable(true);

    // Connection
    connect(ui->actionNew, SIGNAL(triggered(bool)),
            this, SLOT(newFile()));
}

MainWindow::~MainWindow()
{
    delete ui;

    foreach (Canvas* const c, d->canvases.values())
    {
        delete c;
    }

    delete d;
}

void MainWindow::newFile()
{
    Canvas* c = new Canvas(d->tabWidget);
    int tabIndex = d->tabWidget->addTab(c->view(), "New File");
    c->setTabIndex(tabIndex);
    d->canvases.insert(tabIndex, c);

    connect(d->tabWidget, SIGNAL(tabCloseRequested(int)),
            c, SLOT(tabAboutToBeClosed(int)));

    connect(c, SIGNAL(confirmTabClose(int)),
            this, SLOT(closeTab(int)));
}

void MainWindow::closeTab(int tabIndex)
{
    qDebug() << "Tab is closing: " << tabIndex;
    QHash<int, Canvas*>::iterator it = d->canvases.find(tabIndex);
    if(it != d->canvases.end())
    {
        delete it.value();
        d->canvases.erase(it);

        QHash<int, Canvas*>::iterator it2 = d->canvases.find(tabIndex+1);
        int tmp = tabIndex;
        while (it2 != d->canvases.end())
        {
            it2.value()->setTabIndex(tmp++);
            ++it2;
        }
        d->tabWidget->removeTab(tabIndex);
    }
}

} // namespace Logicsim
