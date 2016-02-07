#ifndef CANVASMANAGER_H
#define CANVASMANAGER_H

// Qt includes

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDebug>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QList>

// Local includes

#include "logicsim_global.h"
#include "graphicgate.h"

namespace Logicsim
{

class Cell
{
public:
    Cell() : m_col(0), m_row(0) {}
    Cell(int col, int row) : m_col(col), m_row(row) {}

    inline bool isNull()
    { return (m_col == 0) && (m_row == 0); }

    inline int row()
    { return m_row; }

    inline int col()
    { return m_col; }

    inline void setCol(int c)
    { m_col = c; }

    inline void setRow(int r)
    { m_row = r; }

    inline void erase()
    { m_col = 0; m_row = 0; }

private:
    int m_col, m_row ;
};

class CanvasManager : public QObject
{
    Q_OBJECT
public:
    CanvasManager(QObject *parent = 0, QGraphicsScene *canvas = 0);
    ~CanvasManager();

    QList<GraphicGate *> gates();
    QGraphicsScene* canvas();

    void addGate(GraphicGate* gate, QPointF scenePos);
    void selectGate(GraphicGate* gate);
    void unSelectGate(GraphicGate* gate);
    void deleteGate(int index);
    void movingGate(GraphicGate* gate);
    void gateMoved(GraphicGate* gate, QPointF scenePos);

private:
    Cell findSuitableCell(QPointF scenePos);
    void parkGate(GraphicGate* g, Cell c);
    QList<Cell> alternativePlaces(Cell c) const;
    int calculateSquareNumber(Cell c) const;
    int selectedGateSquare(int index) const;

Q_SIGNALS:
    void gateCreated();

private:
    class Private;
    Private* const d;
};

}

#endif // CANVASMANAGER_H
