#include "canvasmanager.h"

// Qt includes

#include <QtMath>

namespace Logicsim
{

class CanvasManager::Private
{
public:
    Private() :
        gatesCount(0),
        canvas(0),
        oldSquareNumberOfMovingGate(0)
    {}

    QList<GraphicGate *> mGates;
    QList<QPointF>       mGatePositions;
    int                  gatesCount;
    QGraphicsScene*      canvas;
    QSet<int>            acquiredSquares;
    int                  oldSquareNumberOfMovingGate;
    Cell                 oldCellOfMovingGate;
    int gateId;
};

CanvasManager::CanvasManager(QObject *parent, QGraphicsScene *canvas) : QObject(parent), d(new Private)
{
    d->gateId = 0;
    d->canvas = canvas;
}

QList<GraphicGate *> CanvasManager::gates()
{
    return d->mGates;
}

QGraphicsScene *CanvasManager::canvas()
{
    return d->canvas;
}

void CanvasManager::addGate(GraphicGate *gate, QPointF scenePos)
{
    Cell c = findSuitableCell(scenePos);
    if (!c.isNull())
    {
        parkGate(gate, c);
        int squareNumber = calculateSquareNumber(c);
        d->acquiredSquares.insert(squareNumber);
     /*   gate->setName("gate " + QString::number(d->gateId));
        d->gateId++;*/
        d->canvas->addItem(gate);
        d->gatesCount++;
        d->mGates << gate;
        emit gateCreated();
    }
}

void CanvasManager::deleteGate(int index)
{
    d->canvas->removeItem(d->mGates.at(index));
    d->mGates.removeAt(index);
}
void CanvasManager::movingGate(GraphicGate *gate)
{
    if (d->oldSquareNumberOfMovingGate != 0)
        return;

    qreal x = gate->pos().x() + gate->boundingRect().width()/2;
    qreal y = gate->pos().y() + gate->boundingRect().height()/2;

    int col = ((x - GRID_STEP/2) / GRID_STEP) + 1;
    int row = ((y - GRID_STEP/2) / GRID_STEP) + 1;

    d->oldCellOfMovingGate.setCol(col);
    d->oldCellOfMovingGate.setRow(row);
    d->oldSquareNumberOfMovingGate = calculateSquareNumber(d->oldCellOfMovingGate);
}

void CanvasManager::gateMoved(GraphicGate* gate, QPointF scenePos)
{
    Cell newCell = findSuitableCell(scenePos);

    if(!newCell.isNull() && calculateSquareNumber(newCell) != d->oldSquareNumberOfMovingGate)
    {
        qDebug() << "Gate Moved";
        parkGate(gate, newCell);
        d->acquiredSquares.remove(d->oldSquareNumberOfMovingGate);
        d->acquiredSquares.insert(calculateSquareNumber(newCell));
    }
    else
    {
        qDebug() << "Gate Not Moved";
        parkGate(gate, d->oldCellOfMovingGate);
    }

    d->oldCellOfMovingGate.erase();
    d->oldSquareNumberOfMovingGate = 0;
}

Cell CanvasManager::findSuitableCell(QPointF scenePos)
{
    int col = qCeil(scenePos.x() / GRID_STEP);
    int row = qCeil(scenePos.y() / GRID_STEP);
    Cell c(col, row);
    int squareNumber = calculateSquareNumber(c);

    if (d->acquiredSquares.contains(squareNumber) && squareNumber != d->oldSquareNumberOfMovingGate)
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

void CanvasManager::parkGate(GraphicGate * g, Cell c)
{
    qreal x = (c.col() - 1) * GRID_STEP + GRID_STEP/2;
    qreal y = (c.row() - 1) * GRID_STEP + GRID_STEP/2;

    g->setPos(x - g->boundingRect().width()/2,
              y - g->boundingRect().height()/2);
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

CanvasManager::~CanvasManager()
{
    delete d;
}

} // namespace Logicsim
