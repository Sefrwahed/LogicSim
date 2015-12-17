#include "canvasmanager.h"

namespace Logicsim
{

class CanvasManager::Private
{
public:
    Private() :
        objectsCount(0)
    {}
    QList<GraphicGate *> mGates;
    int objectsCount;
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
    d->canvas->addItem(g);
    d->objectsCount++;
    d->mGates << g;
    qDebug() << g->pos();
}

CanvasManager::~CanvasManager()
{
    delete d;
}



}
