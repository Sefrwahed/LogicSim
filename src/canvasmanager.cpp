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
        selectedComponentIndex(-1),
        selectedLineIndex(-1),
        componentId(0),
        oldSquareNumberOfMovingComponent(0),
        selectedComponent(0),
        canvas(0),
        selectedInput(0),
        selectedOutput(0),
        selectedLine(0)
    {}

    int                    componentCount;
    int                    selectedComponentIndex;
    int                    selectedLineIndex;
    int                    componentId;
    int                    oldSquareNumberOfMovingComponent;
    Component*             selectedComponent;
    QGraphicsScene*        canvas;
    Pin*                   selectedInput;
    Pin*                   selectedOutput;
    Cell                   oldCellOfMovingComponent;
    QSet<int>              acquiredSquares;
    QList<Component *>     mComponents;
    QList<ConnectionLine*> connectionLines;
    ConnectionLine* selectedLine;
};

CanvasManager::CanvasManager(QObject *parent, QGraphicsScene *canvas)
    : QObject(parent), d(new Private)
{
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

int CanvasManager::selectedComponentIndex()
{
    return d->selectedComponentIndex;
}

int CanvasManager::selectedLineIndex()
{
    return d->selectedLineIndex;
}

void CanvasManager::addComponent(Component *component, QPointF scenePos)
{
    Cell c = findSuitableCell(scenePos);
    if (!c.isNull())
    {
        parkComponent(component, c);
        int squareNumber = calculateSquareNumber(c);
        d->acquiredSquares.insert(squareNumber);
        component->setName("component " + QString::number(d->componentId++));
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
    if(d->selectedComponent != 0)
    {
        qDebug() << "Unselected: " << d->selectedComponent->name();
        d->selectedComponentIndex = -1;
        d->selectedComponent->setSelection(false);
        d->selectedComponent = 0;
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

void CanvasManager::pinPressed(Pin *p)
{
    if(p->type() == Pin::Input)
    {
        if(p->isConnected())
        {
            d->selectedOutput = 0;
            return;
        }

        qDebug() << "Disconnected Input pin was clicked";
        d->selectedInput = p;
    }
    else
    {
        qDebug() << "Output pin was clicked";
        d->selectedOutput = p;
    }

    if(d->selectedInput && d->selectedOutput
            && d->selectedInput->parentComponent() != d->selectedOutput->parentComponent())
    {
        ConnectionLine* line = new ConnectionLine(d->selectedInput, d->selectedOutput);
        line->setZValue(-1);
        d->selectedInput->setConnected(line);
        d->selectedOutput->setConnected(line);
        d->connectionLines.append(line);

        connect(line, SIGNAL(lineSelected()),
                this, SLOT(selectLine()));

        d->canvas->addItem(line);

        d->selectedInput = 0;
        d->selectedOutput = 0;
    }

    qDebug() << "Selected input: " << d->selectedInput;
    qDebug() << "Selected output: " << d->selectedOutput;

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
    component->updateConnection();
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

void CanvasManager::renameComponent(QTableWidgetItem *item)
{
    if(item->row() < d->componentCount)
    {
        d->mComponents.at(item->row())->setName(item->text());
    }
}

void CanvasManager::selectLine()
{
    d->selectedLine = static_cast<ConnectionLine*>(sender());
    d->selectedLineIndex = d->connectionLines.indexOf(d->selectedLine);
}

void CanvasManager::unSelectLine()
{
    if(d->selectedLine != 0)
    {
        d->selectedLine = 0;
        d->selectedLineIndex = -1;
    }
}

void CanvasManager::deleteLine(int index)
{
    unSelectLine();
    d->canvas->removeItem(d->connectionLines.at(index));
    d->connectionLines.removeAt(index);
}

CanvasManager::~CanvasManager()
{
    delete d;
}

} // namespace Logicsim
