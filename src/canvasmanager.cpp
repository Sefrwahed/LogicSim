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
    for(i = 0; i < d->gatesCount; i++)
    {
        //check overlapping
        if(gate->collidesWithItem(d->mGates.at(i),Qt::IntersectsItemShape))
        {
            addable = false;
            break;
        }
    }
    if(addable){
        d->canvas->addItem(gate);
        d->gatesCount++;
        d->mGates << gate;
    }
    else
    {
        if(d->mGates.at(i)->pos().rx() < gate->pos().rx())
            gate->setX(d->mGates.at(i)->pos().rx() + gate->boundingRect().width() + GATE_X_MARGIN);
        else
            gate->setX(d->mGates.at(i)->pos().rx() - gate->boundingRect().width() - GATE_X_MARGIN);
        addGate(gate); //using recursion
    }
}

void CanvasManager::moveGate()
{
    GraphicGate *gate = static_cast<GraphicGate*>(d->canvas->mouseGrabberItem());
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
        if(d->mGates.at(i)->pos().rx() < gate->pos().rx())
            gate->setX(d->mGates.at(i)->pos().rx() + gate->boundingRect().width() + GATE_X_MARGIN);
        else
            gate->setX(d->mGates.at(i)->pos().rx() - gate->boundingRect().width() - GATE_X_MARGIN);
        moveGate(); //using recursion
    }
}

CanvasManager::~CanvasManager()
{
    delete d;
}

}
