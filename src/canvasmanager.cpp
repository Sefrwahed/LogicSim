#include "canvasmanager.h"

// Qt includes

#include <QtMath>

namespace Logicsim
{

class CanvasManager::Private
{
public:
    Private() :
        componentCount(0),
        canvas(0),
        oldSquareNumberOfMovingComponent(0)
    {}

    QList<Component *> mComponents;
    QList<QPointF>       mGatePositions;
    int                  componentCount;
    QGraphicsScene*      canvas;
    QSet<int>            acquiredSquares;
    int                  oldSquareNumberOfMovingComponent;
    Cell                 oldCellOfMovingComponent;
    Component *selectedComponent;
    int selectedComponentIndex;
    int componentId;
};

CanvasManager::CanvasManager(QObject *parent, QGraphicsScene *canvas) : QObject(parent), d(new Private)
{
    d->selectedComponentIndex = -1;
    d->componentId = 0;
    d->selectedComponent = NULL;
    d->canvas = canvas;
}

QList<Component *> CanvasManager::components()
{
    return d->mComponents;
}

QGraphicsScene *CanvasManager::canvas()
{
    return d->canvas;
}

void CanvasManager::addComponent(Component *component, QPointF scenePos)
{
    Cell c = findSuitableCell(scenePos);
    if (!c.isNull())
    {
        parkComponent(component, c);
        int squareNumber = calculateSquareNumber(c);
        d->acquiredSquares.insert(squareNumber);
        component->setName("component " + QString::number(d->componentId));
        d->componentId++;
        d->canvas->addItem(component);
        d->componentCount++;
        d->mComponents << component;
        emit componentAdded(d->componentCount - 1);
    }
}

void CanvasManager::selectComponent(Component *component)
{
    if(d->selectedComponent != component)
    {
        qDebug() << "selected: " << component->name();
        d->selectedComponent = component;
        d->selectedComponentIndex = d->mComponents.indexOf(d->selectedComponent);
        d->selectedComponent->setSelection(true);
        emit componentSelectedFromCanvas(d->mComponents.indexOf(d->selectedComponent));
    }
}

void CanvasManager::unSelectComponent()
{
    if(d->selectedComponent != NULL)
    {
        qDebug() << "Unselected: " << d->selectedComponent->name();
        d->selectedComponentIndex = -1;
        d->selectedComponent->setSelection(false);
        d->selectedComponent = NULL;
    }
}

void CanvasManager::deleteComponent(int index)
{
    unSelectComponent();
    d->canvas->removeItem(d->mComponents.at(index));
    d->acquiredSquares.remove(selectedComponentSquare(index));
    d->mComponents.removeAt(index);
    d->componentCount--;
    emit componentDeleted(index);
}

void CanvasManager::movingComponent(Component *component)
{
    if (d->oldSquareNumberOfMovingComponent != 0)
        return;

    qreal x = component->pos().x() + component->boundingRect().width()/2;
    qreal y = component->pos().y() + component->boundingRect().height()/2;

    int col = ((x - GRID_STEP/2) / GRID_STEP) + 1;
    int row = ((y - GRID_STEP/2) / GRID_STEP) + 1;

    d->oldCellOfMovingComponent.setCol(col);
    d->oldCellOfMovingComponent.setRow(row);
    d->oldSquareNumberOfMovingComponent = calculateSquareNumber(d->oldCellOfMovingComponent);
}

void CanvasManager::componentMoved(Component* component, QPointF scenePos)
{
    Cell newCell = findSuitableCell(scenePos);
    if(!newCell.isNull() &&
       calculateSquareNumber(newCell) != d->oldSquareNumberOfMovingComponent &&
       scenePos.x() > 0 && scenePos.y() > 0 &&
       scenePos.x() < CANVAS_WIDTH && scenePos.y() < CANVAS_HEIGHT)
    {
        qDebug() << "Gate Moved";
        parkComponent(component, newCell);
        d->acquiredSquares.remove(d->oldSquareNumberOfMovingComponent);
        d->acquiredSquares.insert(calculateSquareNumber(newCell));
    }
    else
    {
        qDebug() << "Gate Not Moved";
        parkComponent(component, d->oldCellOfMovingComponent);
    }

    d->oldCellOfMovingComponent.erase();
    d->oldSquareNumberOfMovingComponent = 0;
}

int CanvasManager::selectedComponentIndex()
{
    return d->selectedComponentIndex;
}

Cell CanvasManager::findSuitableCell(QPointF scenePos)
{
    int col = qCeil(scenePos.x() / GRID_STEP);
    int row = qCeil(scenePos.y() / GRID_STEP);
    Cell c(col, row);
    int squareNumber = calculateSquareNumber(c);

    if (d->acquiredSquares.contains(squareNumber) && squareNumber != d->oldSquareNumberOfMovingComponent)
    {
        foreach(Cell i, alternativePlaces(c))
        {
            int alternativeSquareNumber = calculateSquareNumber(i);

            if(!d->acquiredSquares.contains(alternativeSquareNumber))
            {
                squareNumber = alternativeSquareNumber;

                return i;
            }
        }
    }
    else
    {
        return c;
    }

    return Cell();
}

void CanvasManager::parkComponent(Component * component, Cell c)
{
    qreal x = (c.col() - 1) * GRID_STEP + GRID_STEP/2;
    qreal y = (c.row() - 1) * GRID_STEP + GRID_STEP/2;

    component->setPos(x - component->boundingRect().width()/2,
              y - component->boundingRect().height()/2);
}

QList<Cell> CanvasManager::alternativePlaces(Cell c) const
{
    QList<Cell> cells;
    int col = c.col();
    int row = c.row();

    if(col - 1 >= 1)
    {
        cells << Cell(col - 1, row);
    }

    if(col + 1 <= NUMBER_OF_SQUARES_IN_ROW)
    {
        cells << Cell(col + 1, row);
    }

    if(row - 1 >= 1)
    {
        cells << Cell(col, row - 1);

        if(col - 1 >= 1)
            cells << Cell(col - 1, row - 1);

        if(col + 1 <= NUMBER_OF_SQUARES_IN_ROW)
            cells << Cell(col + 1, row - 1);
    }

    if(row + 1 <= NUMBER_OF_SQUARES_IN_COLUMN)
    {
        cells << Cell(col, row + 1);

        if(col - 1 >= 1)
            cells << Cell(col - 1, row + 1);

        if(col + 1 <= NUMBER_OF_SQUARES_IN_ROW)
            cells << Cell(col + 1, row + 1);
    }

    return cells;
}

int CanvasManager::calculateSquareNumber(Cell c) const
{
    return c.col() + ((c.row() - 1) * NUMBER_OF_SQUARES_IN_ROW);
}

int CanvasManager::selectedComponentSquare(int index) const
{
    QPointF position = d->mComponents.at(index)->pos();
    int col = qCeil(position.x() / GRID_STEP);
    int row = qCeil(position.y() / GRID_STEP);
    Cell c(col, row);
    return calculateSquareNumber(c);
}

void CanvasManager::selectedFromWorkspace(int index)
{
    unSelectComponent();
    selectComponent(d->mComponents.at(index));
}

CanvasManager::~CanvasManager()
{
    delete d;
}

} // namespace Logicsim
