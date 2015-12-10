#include "canvasmanager.h"

namespace Logicsim
{

class CanvasManager::Private
{
public:
    Private() :
        objectsCount(0)
    {}
    int objectsCount;
    QGraphicsScene *canvas;
};


CanvasManager::CanvasManager(QObject *parent, QGraphicsScene *canvas) : QObject(parent), d(new Private)
{
    d->canvas = canvas;
}

QList<QGraphicsItem *> CanvasManager::items()
{
    return d->canvas->items();
}

QGraphicsScene *CanvasManager::canvas()
{
    return d->canvas;
}

CanvasManager::~CanvasManager()
{
    delete d;
}



}
