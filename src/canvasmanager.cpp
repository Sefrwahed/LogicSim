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
    bool checkOverlapping(GraphicGate* g)
    {


    }
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
    QPointF distance;
    bool addable = true;
    int i;
    for(i = 0; i < d->gatesCount; i++)
    {
        distance = d->mGates.at(i)->mapFromParent(g->pos());
        //check overlapping
        if((distance.rx() > -1*(g->boundingRect().width() + GATE_X_MARGIN)
            && distance.rx() < g->boundingRect().width() + GATE_X_MARGIN)
            &&(distance.ry() > -1*(g->boundingRect().height() + GATE_Y_MARGIN)
            && distance.ry() < (g->boundingRect().height() + GATE_Y_MARGIN)))
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
        addGate(g);
    }
}

void CanvasManager::moveGate(QGraphicsSceneMouseEvent *event)
{
}

CanvasManager::~CanvasManager()
{
    delete d;
}

}
