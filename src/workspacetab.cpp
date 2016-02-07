#include "workspacetab.h"

namespace Logicsim
{

class WorkspaceTab::Private
{
public:
    Private() :
        tabIndex(-1),
        gatesCount(0)
    {}
    int tabIndex;
    int gatesCount;
    CanvasManager *currentCanvasManager;
};

WorkspaceTab::WorkspaceTab(QWidget *parent) : QTableWidget(parent), d(new Private)
{
    verticalHeader()->setVisible(false);
    horizontalHeader()->setVisible(false);
    setSelectionMode(QAbstractItemView::SingleSelection); // TODO remove this
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setColumnCount(1);
    setRowCount(0);
    setShowGrid(false);

    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

WorkspaceTab::~WorkspaceTab()
{
    delete d->currentCanvasManager;
    delete d;
}

void WorkspaceTab::setManager(CanvasManager *canvasManager)
{
    disconnect(this, SIGNAL(gateSelectedFromWorkspace(int)), d->currentCanvasManager, SLOT(selectedFromWorkspace(int)));
    disconnect(d->currentCanvasManager, SIGNAL(gateSelectedFromCanvas(int)), this, SLOT(selectedFromCanvas(int)));
    disconnect(d->currentCanvasManager, SIGNAL(gateAdded(int)), this, SLOT(addGateToWorkspace(int)));
    disconnect(d->currentCanvasManager, SIGNAL(gateDeleted(int)), this, SLOT(removeGateFromWorkspace(int)));
  //  disconnect(d->currentCanvasManager, SIGNAL(gatesUpdated()), this, SLOT(updateGates()));
    d->currentCanvasManager = canvasManager;
//    connect(d->currentCanvasManager, SIGNAL(gatesUpdated()), this, SLOT(updateGates()));
    connect(d->currentCanvasManager, SIGNAL(gateAdded(int)), this, SLOT(addGateToWorkspace(int)));
    connect(d->currentCanvasManager, SIGNAL(gateDeleted(int)), this, SLOT(removeGateFromWorkspace(int)));
    connect(d->currentCanvasManager, SIGNAL(gateSelectedFromCanvas(int)), this, SLOT(selectedFromCanvas(int)));
    connect(this, SIGNAL(gateSelectedFromWorkspace(int)), d->currentCanvasManager, SLOT(selectedFromWorkspace(int)));
}

void WorkspaceTab::updateGates()
{
    clear();
    qDebug() << "hello " << d->currentCanvasManager->gates().length();
    if(d->currentCanvasManager != NULL)
    {
        d->gatesCount = d->currentCanvasManager->gates().length();
        setRowCount(d->gatesCount);
        for(int i = 0; i < d->gatesCount; i++)
        {
            QTableWidgetItem* item = new QTableWidgetItem(d->currentCanvasManager->gates().at(i)->name());
            setItem(i,0,item);
        }
    }
}

void WorkspaceTab::addGateToWorkspace(int index)
{
    setRowCount(d->gatesCount+1);
    QTableWidgetItem* item = new QTableWidgetItem(d->currentCanvasManager->gates().at(index)->name());
    setItem(d->gatesCount,0,item);
    d->gatesCount++;
}

void WorkspaceTab::removeGateFromWorkspace(int index)
{
    removeRow(index);
    d->gatesCount--;
}

void WorkspaceTab::selectedFromCanvas(int index)
{
    selectRow(index);
}

void WorkspaceTab::keyPressEvent(QKeyEvent *event)
{
  switch (event->key())
  {
    case Qt::Key_Delete:
        qDebug() << "Delete";
        if(selectedIndexes().length() == 1)
        {
            int row = selectedIndexes().at(0).row();
                        qDebug() << row;
            d->currentCanvasManager->deleteGate(row);
        }
    break;
  }
}

void WorkspaceTab::mousePressEvent(QMouseEvent *event)
{
    QTableWidget::mousePressEvent(event);

    emit gateSelectedFromWorkspace(selectedItems().at(0)->row());
}

}
