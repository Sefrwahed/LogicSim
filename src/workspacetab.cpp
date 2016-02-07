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
    CanvasManager *currentCanvasManager;
};

WorkspaceTab::WorkspaceTab(QWidget *parent) : QTableWidget(parent), d(new Private)
{
    verticalHeader()->setVisible(false);
    horizontalHeader()->setVisible(false);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setColumnCount(1);
    setRowCount(0);
    setShowGrid(false);

    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

WorkspaceTab::~WorkspaceTab()
{
}

void WorkspaceTab::setManager(CanvasManager *canvasManager)
{
    disconnect(d->currentCanvasManager, SIGNAL(gateSelectedFromCanvas(int)), this, SLOT(selectedFromCanvas(int)));
    disconnect(d->currentCanvasManager, SIGNAL(gateCreated()), this, SLOT(updateGates()));
    d->currentCanvasManager = canvasManager;
    clear();
    connect(d->currentCanvasManager, SIGNAL(gateCreated()), this, SLOT(updateGates()));
    connect(d->currentCanvasManager, SIGNAL(gateSelectedFromCanvas(int)), this, SLOT(selectedFromCanvas(int)));
}

void WorkspaceTab::updateGates()
{
    if(d->currentCanvasManager != NULL)
    {
        qDebug() << "manager" << d->currentCanvasManager->gates().length();
        setRowCount(d->currentCanvasManager->gates().length());
        for(int i = 0; i < d->currentCanvasManager->gates().length(); i++)
        {
            QTableWidgetItem* item = new QTableWidgetItem(d->currentCanvasManager->gates().at(i)->name());
            setItem(i,0,item);
        }
    }
}

void WorkspaceTab::selectedFromCanvas(int index)
{
    qDebug() << index;
    selectRow(index);
}

void WorkspaceTab::keyPressEvent(QKeyEvent *event)
{
  switch (event->key())
  {
    case Qt::Key_Delete:
        qDebug() << "Delete";
        for(int i = 0, n = selectedIndexes().length(); i < n; i++)
        {
            int row = selectedIndexes().at(i).row();
            d->currentCanvasManager->deleteGate(row);
            removeRow(row);
        }
    break;
  }
}

}
