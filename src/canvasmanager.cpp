#include "canvasmanager.h"

// Qt includes

#include <QtMath>

namespace Logicsim
{

class CanvasManager::Private
{
public:
    Private() :
        gatesCount(0)
    {}
    QList<GraphicGate *> mGates;
    QList<QPointF>       mGatePositions;
    int                  gatesCount;
    QGraphicsScene*      canvas;
    QVector<int>         acquiredSquares;

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
    int col = qCeil(scenePos.x() / GRID_STEP);
    int row = qCeil(scenePos.y() / GRID_STEP);
    int squareNumber = col + ((row - 1) * NUMBER_OF_SQUARES_IN_ROW);

    qDebug() << "Dropped on square number: " << (squareNumber);

    if (!d->acquiredSquares.contains(squareNumber))
    {
        qreal x = (col - 1) * GRID_STEP + GRID_STEP/2;
        qreal y = (row - 1) * GRID_STEP + GRID_STEP/2;

        qDebug() << "X: " << x << " Y: " << y;

        gate->setPos(x - gate->boundingRect().width()/2,
                     y - gate->boundingRect().height()/2);

        d->acquiredSquares.append(squareNumber);

        d->stayInScene(gate);
        d->avoidCollision(gate);
        d->canvas->addItem(gate);
        d->gatesCount++;
        d->mGates << gate;
    }
}

void CanvasManager::moveGate(GraphicGate* gate)
{
    d->avoidCollision(gate);
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
