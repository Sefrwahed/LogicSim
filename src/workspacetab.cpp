#include "workspacetab.h"

namespace Logicsim
{

class WorkspaceTab::Private
{
public:
    Private() :
        tabIndex(-1),
        componentsCount(0),
        currentCanvasManager(0)
    {}
    int tabIndex;
    int componentsCount;
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
}

WorkspaceTab::~WorkspaceTab()
{
    delete d->currentCanvasManager;
    delete d;
}

void WorkspaceTab::setManager(CanvasManager *canvasManager)
{
    if(d->currentCanvasManager != 0)
    {
        disconnect(this, SIGNAL(itemChanged(QTableWidgetItem*)),
                   d->currentCanvasManager, SLOT(renameComponent(QTableWidgetItem*)));
        disconnect(this, SIGNAL(componentSelectedFromWorkspace(int)),
                   d->currentCanvasManager, SLOT(selectedFromWorkspace(int)));
        disconnect(d->currentCanvasManager, SIGNAL(componentSelectedFromCanvas(int)),
                   this, SLOT(selectedFromCanvas(int)));
        disconnect(d->currentCanvasManager, SIGNAL(componentAdded(int)),
                   this, SLOT(addComponentsToWorkspace(int)));
        disconnect(d->currentCanvasManager, SIGNAL(componentDeleted(int)),
                   this, SLOT(removeComponentsFromWorkspace(int)));
    }
    d->currentCanvasManager = canvasManager;
    connect(d->currentCanvasManager, SIGNAL(componentAdded(int)),
            this, SLOT(addComponentsToWorkspace(int)));
    connect(d->currentCanvasManager, SIGNAL(componentDeleted(int)),
            this, SLOT(removeComponentsFromWorkspace(int)));
    connect(d->currentCanvasManager, SIGNAL(componentSelectedFromCanvas(int)),
            this, SLOT(selectedFromCanvas(int)));
    connect(this, SIGNAL(componentSelectedFromWorkspace(int)),
            d->currentCanvasManager, SLOT(selectedFromWorkspace(int)));
    connect(this, SIGNAL(itemChanged(QTableWidgetItem*)),
            d->currentCanvasManager, SLOT(renameComponent(QTableWidgetItem*)));
}

void WorkspaceTab::updateComponents()
{
    clear();
    if(d->currentCanvasManager != 0)
    {
        d->componentsCount = d->currentCanvasManager->components().length();
        setRowCount(d->componentsCount);
        for(int i = 0; i < d->componentsCount; i++)
        {
            QTableWidgetItem* item = new QTableWidgetItem(d->currentCanvasManager->components().at(i)->name());
            setItem(i,0,item);
        }
    }
}

void WorkspaceTab::addComponentsToWorkspace(int index)
{
    setRowCount(d->componentsCount+1);
    QTableWidgetItem* item = new QTableWidgetItem(d->currentCanvasManager->components().at(index)->name());
    setItem(d->componentsCount,0,item);
    d->componentsCount++;
}

void WorkspaceTab::removeComponentsFromWorkspace(int index)
{
    removeRow(index);
    d->componentsCount--;
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
            d->currentCanvasManager->deleteComponent(row);
        }
    break;
  }
}

void WorkspaceTab::mousePressEvent(QMouseEvent *event)
{
    QTableWidget::mousePressEvent(event);

    emit componentSelectedFromWorkspace(selectedItems().at(0)->row());
}

}
