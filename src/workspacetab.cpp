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
    CanvasManager *mCanvasManager;
};

WorkspaceTab::WorkspaceTab(QWidget *parent) : QTableWidget(parent), d(new Private)
{
    verticalHeader()->setVisible(false);
    horizontalHeader()->setVisible(false);

    setColumnCount(1);
    setRowCount(0);
    setShowGrid(false);

    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

WorkspaceTab::~WorkspaceTab()
{
    disconnect(d->mCanvasManager, SIGNAL(gateCreated()), this, SLOT(updateGates()));
}

void WorkspaceTab::setManager(CanvasManager *canvasManager)
{
    disconnect(d->mCanvasManager, SIGNAL(gateCreated()), this, SLOT(updateGates()));
    d->mCanvasManager = canvasManager;
    clear();
    connect(d->mCanvasManager, SIGNAL(gateCreated()), this, SLOT(updateGates()));
}

void WorkspaceTab::updateGates()
{
    if(d->mCanvasManager != NULL)
    {
        qDebug() << "manager" << d->mCanvasManager->gates().length();
        setRowCount(d->mCanvasManager->gates().length());
        for(int i = 0; i < d->mCanvasManager->gates().length(); i++)
        {
            QTableWidgetItem* item = new QTableWidgetItem("gate");
            setItem(i,0,item);
        }
    }
}


}
