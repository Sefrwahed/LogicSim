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
        squareNumberOfMovingGate(0)
    {}

    QList<GraphicGate *> mGates;
    QList<QPointF>       mGatePositions;
    int                  gatesCount;
    QGraphicsScene*      canvas;
    QSet<int>            acquiredSquares;
    int                  squareNumberOfMovingGate;

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
    bool found = findSuitablePosition(gate, scenePos);
    if (found)
    {
        d->canvas->addItem(gate);
        d->gatesCount++;
        d->mGates << gate;
    }
}

void CanvasManager::movingGate(GraphicGate *gate)
{
    if (d->squareNumberOfMovingGate != 0)
        return;

    qreal x = gate->pos().x() + gate->boundingRect().width()/2;
    qreal y = gate->pos().y() + gate->boundingRect().height()/2;

    int col = ((x - GRID_STEP/2) / GRID_STEP) + 1;
    int row = ((y - GRID_STEP/2) / GRID_STEP) + 1;

    d->squareNumberOfMovingGate = calculateSquareNumber(col, row);
    qDebug() << "Square number of moving Gate: " << d->squareNumberOfMovingGate;
}

void CanvasManager::gateMoved(GraphicGate* gate, QPointF scenePos)
{
    bool moved = findSuitablePosition(gate, scenePos);

    if(moved)
    {
        qDebug() << "Gate Moved ::: " << moved;

        d->acquiredSquares.remove(d->squareNumberOfMovingGate);

        qDebug() << d->acquiredSquares;
        d->squareNumberOfMovingGate = 0;
    }
}

bool CanvasManager::findSuitablePosition(GraphicGate *g, QPointF scenePos)
{
    int col = qCeil(scenePos.x() / GRID_STEP);
    int row = qCeil(scenePos.y() / GRID_STEP);
    int squareNumber = calculateSquareNumber(col,row);
    bool found = true;
    qreal x,y;

    qDebug() << "Dropped on square number: " << (squareNumber);

    if (d->acquiredSquares.contains(squareNumber))
    {
        found = false;
        foreach(QPoint i, alternativePlaces(col, row))
        {
            qDebug() << i;
            col = i.x();
            row = i.y();
            int alternativeSquareNumber = calculateSquareNumber(col, row);

            if(!d->acquiredSquares.contains(alternativeSquareNumber))
            {
                found = true;
                squareNumber = alternativeSquareNumber;
                break;
            }
        }
    }

    if(found)
    {
        x = (col - 1) * GRID_STEP + GRID_STEP/2;
        y = (row - 1) * GRID_STEP + GRID_STEP/2;

        qDebug() << "X: " << x << " Y: " << y;

        g->setPos(x - g->boundingRect().width()/2,
                  y - g->boundingRect().height()/2);

        d->acquiredSquares.insert(squareNumber);
        qDebug() << d->acquiredSquares;
    }

    return found;
}

QList<QPoint> CanvasManager::alternativePlaces(int col, int row) const
{
    QList<QPoint> colsAndRows;

    if(col - 1 >= 1)
    {
        colsAndRows << QPoint(col - 1, row);
    }

    if(col + 1 <= NUMBER_OF_SQUARES_IN_ROW)
    {
        colsAndRows << QPoint(col + 1, row);
    }

    if(row - 1 >= 1)
    {
        colsAndRows << QPoint(col, row - 1);

        if(col - 1 >= 1)
            colsAndRows << QPoint(col - 1, row - 1);

        if(col + 1 <= NUMBER_OF_SQUARES_IN_ROW)
            colsAndRows << QPoint(col + 1, row - 1);
    }

    if(row + 1 <= NUMBER_OF_SQUARES_IN_COLUMN)
    {
        colsAndRows << QPoint(col, row + 1);

        if(col - 1 >= 1)
            colsAndRows << QPoint(col - 1, row + 1);

        if(col + 1 <= NUMBER_OF_SQUARES_IN_ROW)
            colsAndRows << QPoint(col + 1, row + 1);
    }

    return colsAndRows;
}

int CanvasManager::calculateSquareNumber(int col, int row) const
{
    return col + ((row - 1) * NUMBER_OF_SQUARES_IN_ROW);
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
