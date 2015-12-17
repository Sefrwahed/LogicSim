#ifndef CANVASMANAGER_H
#define CANVASMANAGER_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDebug>
#include <QObject>

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
    void addGate(GraphicGate* g);
signals:

public slots:

private:
    class Private;
    Private* const d;
};

}

#endif // CANVASMANAGER_H
