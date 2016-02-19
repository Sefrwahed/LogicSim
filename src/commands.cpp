#include "commands.h"

namespace Logicsim
{

MoveCommand::MoveCommand(Component *Mcomponent, const QPointF &MOldPos,QUndoCommand *parent) : QUndoCommand(parent)
{
    draggedComponent = Mcomponent;
    newPos = Mcomponent->pos();
    oldPos = MOldPos;
}

void MoveCommand::undo()
{
    draggedComponent->setPos(oldPos);
    setText(QObject::tr("Move %1").arg(createCommandString(draggedComponent, newPos)));
}

void MoveCommand::redo()
{
    draggedComponent->setPos(newPos);
    setText(QObject::tr("Move %1").arg(createCommandString(draggedComponent, newPos)));
}

AddCommand::AddCommand(Component *Acomponent, Canvas *Acanvas,QUndoCommand *parent) : QUndoCommand(parent)
{
    static int itemCount = 0;

    canvas = Acanvas;
    addedComponent = Acomponent;
    pos = Acomponent->pos();

    Acanvas->update();
    ++itemCount;
    setText(QObject::tr("Add %1").arg(createCommandString(addedComponent, pos)));
}

AddCommand::~AddCommand()
{
    if (!addedComponent->scene())
        delete addedComponent;
}

void AddCommand::undo()
{
    canvas->removeItem(addedComponent);
    canvas->update();
}

void AddCommand::redo()
{
    canvas->addItem(addedComponent);
    addedComponent->setPos(pos);
    canvas->clearSelection();
    canvas->update();
}

QString createCommandString(Component *item, const QPointF &pos)
{
    return QObject::tr("%2, %3").arg(pos.x()).arg(pos.y());
}

} //LogicSim
