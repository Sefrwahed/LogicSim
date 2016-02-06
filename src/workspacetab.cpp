#include "workspacetab.h"

namespace Logicsim
{

class WorkspaceTab::Private
{
public:
    Private() :
        tabIndex(-1)
    {}
    int tabIndex;
    QList<Canvas*> mCanvases;
};

WorkspaceTab::WorkspaceTab(QWidget *parent) : QTableWidget(parent), d(new Private)
{
    verticalHeader()->setVisible(false);
    horizontalHeader()->setVisible(false);

    setColumnCount(1);
    setRowCount(0);
    setShowGrid(false);

    QTableWidgetItem* item = new QTableWidgetItem("gate");
    setItem(0,0,item);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

WorkspaceTab::~WorkspaceTab()
{

}

void WorkspaceTab::addCanvas(Canvas *canvas)
{
    d->mCanvases << canvas;
}

void WorkspaceTab::currentCanvas(int index)
{
    d->tabIndex = index;
    qDebug() << index;
    qDebug() << d->mCanvases.length();
    updateGates();
}

void WorkspaceTab::updateGates()
{
    CanvasManager *manager = d->mCanvases.at(d->tabIndex)->getCanvasManager();
    setRowCount(manager->gates().length());
    for(int i = 0; i < manager->gates().length(); i++)
    {
        QTableWidgetItem* item = new QTableWidgetItem("gate");
        setItem(i,0,item);
    }
}


}
