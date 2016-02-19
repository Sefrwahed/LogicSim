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

    QGraphicsScene* canvas();
    void setCanvas(QGraphicsScene* s);

    QList<Component *> components();
    Component* componentById(quint32 id);
    void setComponents(QList<Component *> clist);
    int selectedComponentIndex();
    int selectedLineIndex();
    void addComponent(Component* gate, QPointF scenePos);
    void selectComponent(Component* gate);
    void unSelectComponent();
    void deleteComponent(int index);
    void movingComponent(Component* gate);
    void componentMoved(Component* gate, QPointF scenePos);

    void pinPressed(Pin* p);
    void unSelectPins();

    void unSelectLine();
    void deleteLine(int index);

    void pushDataToStream(QDataStream &stream);
    void loadDataFromStream(QDataStream &stream);
    void populateLoadedComponents();

    QString associatedFileName() const;
    void setAssociatedFileName(QString &filename);

    bool isDropable(QPointF position);
    bool isOutOfCanvas(QPointF position);

    bool isDirty() const;
    void setDirty(bool dirty);

private:
    Cell findSuitableCell(QPointF scenePos);
    void parkComponent(Component* g, Cell c);
    QList<Cell> alternativePlaces(Cell c) const;
    int calculateSquareNumber(Cell c) const;
    int selectedComponentSquare(int index) const;
    void addLineToCanvas(ConnectionLine *line);
    void updateComponents();

public Q_SLOTS:
    void selectedFromWorkspace(int index);
    void renameComponent(QTableWidgetItem* item);
    void selectLine();

Q_SIGNALS:
    void componentUpdated();
    void componentDeleted(int index);
    void componentAdded(int index);
    void componentSelectedFromCanvas(int index);

private:
    class Private;
    Private* const d;
};

QDataStream &operator<<(QDataStream &out, CanvasManager * cm);
QDataStream &operator>>(QDataStream &in, CanvasManager *& cm);

}

#endif // CANVASMANAGER_H
