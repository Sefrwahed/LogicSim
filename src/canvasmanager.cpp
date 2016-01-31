#include "canvasmanager.h"

namespace Logicsim
{

class CanvasManager::Private
{
public:
    Private() :
        gatesCount(0)
    {}
    QList<GraphicGate *> mGates;
    int gatesCount;
    QGraphicsScene *canvas;
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

    if(collides)
    {
        if(newGate->pos().rx() < mGates.at(i)->pos().rx()
                && newGate->pos().rx() > newGate->boundingRect().width() + GATE_X_MARGIN)
        {
            newXPos = mGates.at(i)->pos().rx() - newGate->boundingRect().width() - GATE_X_MARGIN;
        }
        else if(newGate->pos().rx() > mGates.at(i)->pos().rx()
                && newGate->pos().rx() <  CANVAS_WIDTH - (newGate->boundingRect().width() + GATE_X_MARGIN))
        {
            newXPos = mGates.at(i)->pos().rx() + newGate->boundingRect().width() + GATE_X_MARGIN;
        }
        else
        {
            if(mGates.at(i)->pos().rx() - mGates.at(i)->boundingRect().width()
               - newGate->boundingRect().width() - GATE_X_MARGIN < 0)
            {
                newXPos = mGates.at(i)->pos().rx() + newGate->boundingRect().width() + GATE_X_MARGIN;
            }
            else
            {
                newXPos = mGates.at(i)->pos().rx() - newGate->boundingRect().width() - GATE_X_MARGIN;
            }
        }

        if(newGate->pos().ry() < mGates.at(i)->pos().ry()
                && newGate->pos().ry() > newGate->boundingRect().height() + GATE_Y_MARGIN)
        {
            newYPos = mGates.at(i)->pos().ry() - newGate->boundingRect().height() - GATE_Y_MARGIN;
        }
        else if(newGate->pos().ry() > mGates.at(i)->pos().ry()
                && newGate->pos().ry() <  CANVAS_HEIGHT - (newGate->boundingRect().height() + GATE_Y_MARGIN))
        {
            newYPos = mGates.at(i)->pos().ry() + newGate->boundingRect().height() + GATE_Y_MARGIN;
        }
        else
        {
            if(mGates.at(i)->pos().ry() - mGates.at(i)->boundingRect().height()
                    - newGate->boundingRect().height() - GATE_Y_MARGIN < 0)
            {
                newYPos = mGates.at(i)->pos().ry() + newGate->boundingRect().height() + GATE_Y_MARGIN;
            }
            else
            {
                newYPos = mGates.at(i)->pos().ry() - newGate->boundingRect().height() - GATE_Y_MARGIN;
            }
        }

        newGate->setX(newXPos);
        newGate->setY(newYPos);
        avoidCollision(newGate);
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
