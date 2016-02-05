#ifndef CANVASMANAGER_H
#define CANVASMANAGER_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDebug>
#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include "logicsim_global.h"
#include "graphicgate.h"

namespace Logicsim
{

class CanvasManager : public QObject
{
    Q_OBJECT
public:
    CanvasManager(QObject *parent = 0, QGraphicsScene *canvas = 0);
    ~CanvasManager();
    QList<GraphicGate *> gates();
    QGraphicsScene* canvas();
    void addGate(GraphicGate* gate);
    void addGate(GraphicGate* gate, QPointF scenePos);
    void moveGate(GraphicGate* gate);

private:
    QPointF findPosition(int col, int row);
    int nearestEmptySquare(int acquiredSquare);

private:
    class Private;
    Private* const d;
};

}

#endif // CANVASMANAGER_H
