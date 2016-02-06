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

    void avoidCollision(GraphicGate* newGate);
    void stayInScene(GraphicGate* Gate);
};

CanvasManager::CanvasManager(QObject *parent, QGraphicsScene *canvas) : QObject(parent), d(new Private)
{
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

void CanvasManager::addGate(GraphicGate* gate)
{
    d->stayInScene(gate);
    d->avoidCollision(gate);
    d->canvas->addItem(gate);
    d->gatesCount++;
    d->mGates << gate;
}

void CanvasManager::addGate(GraphicGate *gate, QPointF scenePos)
{
    Cell c = findSuitableCell(scenePos);
    if (!c.isNull())
    {
        parkGate(gate, c);
        int squareNumber = calculateSquareNumber(c);
        d->acquiredSquares.insert(squareNumber);
        qDebug() << d->acquiredSquares;
        d->canvas->addItem(gate);
        d->gatesCount++;
        d->mGates << gate;
    }
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
    qDebug() << "Square number of moving Gate: " << d->oldSquareNumberOfMovingGate;
}

void CanvasManager::gateMoved(GraphicGate* gate, QPointF scenePos)
{
    Cell newCell = findSuitableCell(scenePos);

    if(!newCell.isNull())
    {
        qDebug() << "Gate Moved";
        parkGate(gate, newCell);
        d->acquiredSquares.insert(calculateSquareNumber(newCell));
        d->acquiredSquares.remove(d->oldSquareNumberOfMovingGate);
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

    if (d->acquiredSquares.contains(squareNumber))
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

    qDebug() << "X: " << x << " Y: " << y;

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

void CanvasManager::Private::avoidCollision(GraphicGate* newGate)
{
    bool collides = false;
    int i;
    qreal newXPos, newYPos;
    for(i = 0; i < gatesCount; i++)
    {
        // skip grabbed gate
        if(newGate == mGates.at(i))
            continue;

        //check overlapping
        if(newGate->collidesWithItem(mGates.at(i), Qt::IntersectsItemShape))
        {
            collides = true;
            break;
        }
    }
    newXPos = newGate->pos().rx();
    newYPos = newGate->pos().ry();
    if(collides)
    {
        qDebug() << newGate->pos();
        if(newXPos < mGates.at(i)->pos().rx()
                && newXPos > newGate->boundingRect().width()
                && newYPos < mGates.at(i)->pos().ry()
                && newYPos > newGate->boundingRect().height())
        {
            newXPos = mGates.at(i)->pos().rx() - newGate->boundingRect().width();
            newYPos = mGates.at(i)->pos().ry() - newGate->boundingRect().height();
        }
        else if(newXPos > mGates.at(i)->pos().rx()
                && newXPos <  CANVAS_WIDTH - (newGate->boundingRect().width())
                && newYPos > mGates.at(i)->pos().ry()
                && newYPos <  CANVAS_HEIGHT - (newGate->boundingRect().height()))
        {
            newXPos = mGates.at(i)->pos().rx() + newGate->boundingRect().width();
            newYPos = mGates.at(i)->pos().ry() + newGate->boundingRect().height();
        }
        else if(newXPos < mGates.at(i)->pos().rx()
                && newXPos > newGate->boundingRect().width()
                && newYPos > mGates.at(i)->pos().ry()
                && newYPos <  CANVAS_HEIGHT - (newGate->boundingRect().height()))
        {
            newXPos = mGates.at(i)->pos().rx() - newGate->boundingRect().width();
            newYPos = mGates.at(i)->pos().ry() + newGate->boundingRect().height();
        }
        else if(newXPos > mGates.at(i)->pos().rx()
                && newXPos <  CANVAS_WIDTH - (newGate->boundingRect().width())
                && newYPos < mGates.at(i)->pos().ry()
                && newYPos > newGate->boundingRect().height())
        {
            newXPos = mGates.at(i)->pos().rx() + newGate->boundingRect().width();
            newYPos = mGates.at(i)->pos().ry() - newGate->boundingRect().height();
        }
        else
        {
            if(mGates.at(i)->pos().rx() - mGates.at(i)->boundingRect().width()
               - newGate->boundingRect().width() < 0)
            {
                newXPos = mGates.at(i)->pos().rx() + newGate->boundingRect().width();
            }
            else
            {
                newXPos = mGates.at(i)->pos().rx() - newGate->boundingRect().width();
            }
            if(mGates.at(i)->pos().ry() - mGates.at(i)->boundingRect().height()
                    - newGate->boundingRect().height()< 0)
            {
                newYPos = mGates.at(i)->pos().ry() + newGate->boundingRect().height();
            }
            else
            {
                newYPos = mGates.at(i)->pos().ry() - newGate->boundingRect().height();
            }
        }/*
        if(!mGatePositions.contains(QPointF(newXPos, newYPos)))
        {
            mGatePositions << QPointF(newXPos, newYPos);
        }
        else
        {
            if( newXPos - newGate->boundingRect().width() < 0)
            {
                newXPos = newXPos + newGate->boundingRect().width();
            }
            else
            {
                newXPos = newXPos - newGate->boundingRect().width();
            }
            if(newYPos - newGate->boundingRect().height() < 0)
            {
                newYPos = newYPos + newGate->boundingRect().height();
            }
            else
            {
                newYPos = newYPos - newGate->boundingRect().height();
            }
        }*/
        newGate->setX(newXPos);
        newGate->setY(newYPos);
        avoidCollision(newGate);
    }
    else
    {
        mGatePositions.clear();
    }
}

void CanvasManager::Private::stayInScene(GraphicGate *gate)
{
    if(gate->pos().rx() < GATE_X_MARGIN)
    {
        gate->setX(GATE_X_MARGIN);
    }
    else if(gate->pos().rx() > CANVAS_WIDTH - (gate->boundingRect().width() + GATE_X_MARGIN))
    {
        gate->setX(CANVAS_WIDTH - (gate->boundingRect().width() + GATE_X_MARGIN));
    }
    if(gate->pos().ry() < GATE_Y_MARGIN)
    {
        gate->setY(GATE_Y_MARGIN);
    }
    else if(gate->pos().ry() > CANVAS_HEIGHT - (gate->boundingRect().height() + GATE_Y_MARGIN))
    {
        gate->setY(CANVAS_HEIGHT - (gate->boundingRect().height() + GATE_Y_MARGIN));
    }

}

}
