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
#include "gate.h"
#include "inputoutputcomponents.h"
#include "component.h"

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

    QList<Component *> components();
    QGraphicsScene* canvas();

    void addComponent(Component* gate, QPointF scenePos);
    void selectComponent(Component* gate);
    void unSelectComponent();
    void deleteComponent(int index);
    void movingComponent(Component* gate);
    void componentMoved(Component* gate, QPointF scenePos);
    void pinPressed(Pin* p);

    int selectedComponentIndex();

private:
    Cell findSuitableCell(QPointF scenePos);
    void parkComponent(Component* g, Cell c);
    QList<Cell> alternativePlaces(Cell c) const;
    int calculateSquareNumber(Cell c) const;
    int selectedComponentSquare(int index) const;

public Q_SLOTS:
    void selectedFromWorkspace(int index);
    void renameComponent(QTableWidgetItem* item);

Q_SIGNALS:
    void componentUpdated();
    void componentDeleted(int index);
    void componentAdded(int index);
    void componentSelectedFromCanvas(int index);

private:
    class Private;
    Private* const d;
};

}

#endif // CANVASMANAGER_H
