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
    void avoidCollision(GraphicGate* oldGate, GraphicGate* newGate);
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
    bool addable = true;
    int i;

    d->stayInScene(gate);

    for(i = 0; i < d->gatesCount; i++)
    {
        //check overlapping
        if(gate->collidesWithItem(d->mGates.at(i),Qt::IntersectsItemShape))
        {
            addable = false;
            break;
        }
    }
    if(addable)
    {
        d->canvas->addItem(gate);
        d->gatesCount++;
        d->mGates << gate;
    }
    else
    {
        d->avoidCollision(d->mGates.at(i), gate);
        addGate(gate); //using recursion
    }
}

void CanvasManager::moveGate(GraphicGate* gate)
{
    bool movable = true;
    int i;
    for(i = 0; i < d->gatesCount; i++)
    {
        // skip grabbed gate
        if(gate == d->mGates.at(i))
            continue;

        // check overlapping
        if(gate->collidesWithItem(d->mGates.at(i),Qt::IntersectsItemShape))
        {
            movable = false;
            break;
        }
    }

    if(!movable){
        d->avoidCollision(d->mGates.at(i), gate);
        moveGate(gate); //using recursion
    }
}

CanvasManager::~CanvasManager()
{
    delete d;
}

void CanvasManager::Private::avoidCollision(GraphicGate* oldGate, GraphicGate* newGate)
{
    if(oldGate->pos().rx() < newGate->pos().rx()
            && newGate->pos().rx() <  CANVAS_WIDTH - (newGate->boundingRect().width() + GATE_X_MARGIN))
    {
        newGate->setX(oldGate->pos().rx() + newGate->boundingRect().width() + GATE_X_MARGIN);
    }
    else if(oldGate->pos().rx() > newGate->pos().rx()
            && newGate->pos().rx() > newGate->boundingRect().width() + GATE_X_MARGIN)
    {
        newGate->setX(oldGate->pos().rx() - newGate->boundingRect().width() - GATE_X_MARGIN);
    }
    if(oldGate->pos().ry() < newGate->pos().ry()
            && newGate->pos().ry() <  newGate->boundingRect().height() + GATE_Y_MARGIN)
    {
        newGate->setY(oldGate->pos().ry() + newGate->boundingRect().height() + GATE_Y_MARGIN);
    }
    else if(oldGate->pos().ry() > newGate->pos().ry()
            && newGate->pos().ry() <  CANVAS_HEIGHT - (newGate->boundingRect().height() + GATE_Y_MARGIN))
    {
        newGate->setY(oldGate->pos().ry() - newGate->boundingRect().height() - GATE_Y_MARGIN);
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
