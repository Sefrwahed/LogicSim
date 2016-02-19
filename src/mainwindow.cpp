#include "mainwindow.h"

// Qt includes

#include <QDebug>
#include <QFileDialog>

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
        activeTabIndex(0),
        tabWidget(0),
        compTab(0),
        workspaceTab(0)
    {}

    int            tabsCount;
    int            activeTabIndex;
    QTabWidget*    tabWidget;
    ComponentsTab* compTab;
    WorkspaceTab*  workspaceTab;
    QList<Canvas*> canvases;

    ~Private()
    {
        foreach (Canvas* c, canvases)
        {
            delete c;
        }
        delete workspaceTab;
        delete compTab;
        delete tabWidget;
    }
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
    /*
    ui->horizontalSlider->setRange(1,11);
    //ui->horizontalSlider->setSingleStep(1);
    ui->horizontalSlider->setFocusPolicy(Qt::StrongFocus);
    ui->horizontalSlider->setTickPosition(QSlider::TicksBothSides);
    ui->horizontalSlider->setTickInterval(1);
*/

    // Connection
    connect(ui->actionNew, SIGNAL(triggered(bool)),
            this, SLOT(newFile()));

    connect(d->tabWidget, SIGNAL(currentChanged(int)),
            this, SLOT(tabChanged(int)));

    connect(d->tabWidget, SIGNAL(tabCloseRequested(int)),
            this, SLOT(tabAboutToBeClosed(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
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
    ui->gridLayout_6->addWidget(d->workspaceTab);
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

void MainWindow::closeEvent(QCloseEvent *e)
{
    appAboutToQuit();
    e->accept();
}

Canvas* MainWindow::newFile()
{
    if(d->tabsCount >= MAX_TAB_COUNT) return 0;

    Canvas* c = new Canvas(d->tabWidget);
    d->canvases << c;
    if(d->tabsCount == 0)
    {
        connect(d->tabWidget, SIGNAL(currentChanged(int)),
                this, SLOT(changeManager(int)));

        connect(d->tabWidget, SIGNAL(currentChanged(int)),
                d->workspaceTab, SLOT(updateComponents()));

        connect(this, SIGNAL(notLastTabClosed(int)),
                this, SLOT(changeManager(int)));

        connect(this, SIGNAL(notLastTabClosed(int)),
                d->workspaceTab, SLOT(updateComponents()));

    }
    d->tabsCount++;
    int tabIndex = d->tabWidget->addTab(c->view(), "New Circuit");
    c->setTabIndex(tabIndex);
    d->tabWidget->setCurrentIndex(tabIndex);
    setMainFrameDisabled(false);
    return c;
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
                   d->workspaceTab, SLOT(updateComponents()));

        disconnect(this, SIGNAL(notLastTabClosed(int)),
                   this, SLOT(changeManager(int)));

        disconnect(this, SIGNAL(notLastTabClosed(int)),
                   d->workspaceTab, SLOT(updateComponents()));

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
    d->workspaceTab->setManager(d->canvases.at(index)->canvasManager());
}

void MainWindow::tabChanged(int index)
{
    d->activeTabIndex = index;
    /*connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),
            d->canvases[d->activeTabIndex],SLOT(Zoom(int)));*/
    connect(ui->Zoomout,SIGNAL(pressed()),
                d->canvases[d->activeTabIndex],SLOT(ZoomOut()));
    connect(ui->zoomin,SIGNAL(pressed()),
                d->canvases[d->activeTabIndex],SLOT(ZoomIn()));

}

void MainWindow::tabAboutToBeClosed(int index)
{
    d->tabWidget->setCurrentIndex(index);
    d->activeTabIndex = index;
    Canvas * c = d->canvases[index];

    if(c->canvasManager()->isDirty())
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Close Tab",
                                      "Do you want to save before closing?",
                                      QMessageBox::Yes|QMessageBox::Cancel|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            qDebug() << "Yes was clicked";
            on_actionSave_triggered();
        }
        else if(reply == QMessageBox::Cancel)
        {
            return;
        }
    }

    closeTab(index);
    return;
}

void MainWindow::setActiveTab(int index)
{
    d->tabWidget->setCurrentIndex(index);
    tabChanged(index);
}

void MainWindow::appAboutToQuit()
{
    foreach(Canvas* c, d->canvases)
    {
        tabAboutToBeClosed(c->tabIndex());
    }
}

void MainWindow::on_actionSave_triggered()
{
    if(d->tabWidget->count() == 0)
        return;

    CanvasManager* c = d->canvases[d->activeTabIndex]->canvasManager();
    QString fileName;

    if( c->associatedFileName().isEmpty() )
    {
        fileName = QFileDialog::getSaveFileName(this,
                tr("Save Circuit"), QDir::home().path(), tr("LogicSim Circuit (*.lsim)"));

        fileName.replace(".lsim", "");
        if(fileName.simplified().isEmpty())
        {
            QMessageBox::warning(this, "Save", "Circuit was not saved!");
            return;
        }


        fileName.append(".lsim");

        qDebug() << fileName;
        c->setAssociatedFileName(fileName);
    }
    else
    {
        fileName = c->associatedFileName();
    }

    qDebug() << "Saving to:" << fileName;
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QDataStream out(&file);
    out << c;
    file.close();
    c->setDirty(false);
    d->tabWidget->setTabText(d->activeTabIndex, QFileInfo(file).baseName());
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Circuit"), QDir::home().path(), tr("LogicSim Circuit (*.lsim)"));

    if(fileName.isEmpty())
        return;

    qDebug() << "Selected File: " << fileName;

    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QDataStream out(&file);
    CanvasManager* cm;
    out >> cm;
    file.close();
    cm->setAssociatedFileName(fileName);

    Canvas * c = newFile();
    if(c)
    {
        c->setManager(cm);
        cm->populateLoadedComponents();
        emit d->tabWidget->currentChanged(c->tabIndex());
        d->tabWidget->setTabText(c->tabIndex(), QFileInfo(file).baseName());
        cm->setDirty(false);
    }
}

} // namespace Logicsim


