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

void CanvasManager::addGate(GraphicGate* g)
{
    bool addable = true;
    int i;
    for(i = 0; i < d->gatesCount; i++)
    {
        //check overlapping
        if(g->collidesWithItem(d->mGates.at(i),Qt::IntersectsItemShape))
        {
            addable = false;
            break;
        }
    }
    if(addable){
        d->canvas->addItem(g);
        d->gatesCount++;
        d->mGates << g;
    }
    else
    {
        if(d->mGates.at(i)->pos().rx() < g->pos().rx())
            g->setX(d->mGates.at(i)->pos().rx() + g->boundingRect().width() + GATE_X_MARGIN);
        else
            g->setX(d->mGates.at(i)->pos().rx() - g->boundingRect().width() - GATE_X_MARGIN);
        addGate(g); //using recursion
    }
}

void CanvasManager::moveGate()
{
    int i;
    for(i = 0; i < d->gatesCount; i++)
    {

    }
}

CanvasManager::~CanvasManager()
{
    delete d;
}

}
