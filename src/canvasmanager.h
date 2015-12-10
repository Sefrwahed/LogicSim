#ifndef CANVASMANAGER_H
#define CANVASMANAGER_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDebug>
#include <QObject>

namespace Logicsim
{

class CanvasManager : public QObject
{
    Q_OBJECT
public:
    CanvasManager(QObject *parent = 0, QGraphicsScene *canvas = 0);
    QList<QGraphicsItem *> items();
    QGraphicsScene* canvas();
    ~CanvasManager();
signals:

public slots:

private:
    class Private;
    Private* const d;
};

}

#endif // CANVASMANAGER_H
