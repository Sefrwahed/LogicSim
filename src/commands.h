#ifndef COMMANDS_H
#define COMMANDS_H

#include <QUndoCommand>

#include "component.h"
#include "canvas.h"

namespace Logicsim
{

class MoveCommand : public QUndoCommand
{
public:
    MoveCommand(Component *Mcomponent, const QPointF &MOldPos,QUndoCommand *parent = 0);
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

private:
    Component *draggedComponent;
    QPointF oldPos;
    QPointF newPos;
};

class AddCommand : public QUndoCommand
{
public:
    AddCommand(Component *Acomponent, Canvas *Acanvas,QUndoCommand *parent = 0);
    ~AddCommand();
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

private:
    Component *addedComponent;
    Canvas *canvas;
    QPointF pos;
};

class DeleteCommand : public QUndoCommand
{
public:
    explicit DeleteCommand(Component* component,Canvas *workingCanvas, QUndoCommand *parent = 0);

    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

private:
    Component *deletedComponent;
    Canvas *canvas;
};

QString createCommandString(Component *item, const QPointF &point);

}
#endif // COMMANDS_H
