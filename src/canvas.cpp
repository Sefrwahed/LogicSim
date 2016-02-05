#include "canvas.h"

// Qt includes

#include <QDebug>
#include <QMessageBox>

// Local includes

#include "logicsim_global.h"

namespace Logicsim
{

class Canvas::Private
{
public:
    Private() :
        tabIndex(-1),
        view(0)
    {}

    int            tabIndex;
    QGraphicsView* view;

};

Canvas::Canvas(QObject *parent)
    : QGraphicsScene(parent), d(new Private)
{
    d->view = new QGraphicsView(this);
    d->view->setSceneRect(0,0, CANVAS_WIDTH, CANVAS_HEIGHT);
}

Canvas::~Canvas()
{
    delete d;
}

QGraphicsView* Canvas::view()
{
    return d->view;
}

int Canvas::tabIndex() const
{
    return d->tabIndex;
}

void Canvas::setTabIndex(int index)
{
    qDebug() << "I am: " << this << " My new tab index: " << index;
    d->tabIndex = index;
}

bool Canvas::tabAboutToBeClosed(int index)
{
    if (index == d->tabIndex)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(d->view, "Test", "Quit?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            qDebug() << "Yes was clicked";
            return true;
        }
    }
    return false;
}


void Canvas::dropEvent(QGraphicsSceneDragDropEvent * event)
{
    if(event->mimeData()->property("acceptable").toBool())
    {
        int typeId = event->mimeData()->property("typeId").toInt();
        event->acceptProposedAction();
        Gate* g = static_cast<Gate*>(QMetaType::create(typeId));
        g->setPos(event->scenePos().x()-g->boundingRect().width()/2,
                  event->scenePos().y()-g->boundingRect().height()/2);
        addItem(g);
    }
    else
    {
        event->setAccepted(false);
    }
}
void Canvas::dragEnterEvent(QGraphicsSceneDragDropEvent * event)
{
    qDebug() << event->mimeData()->property("acceptable");
    if(event->mimeData()->property("acceptable").toBool())
    {
        event->acceptProposedAction();
    }
    else
    {
        event->setAccepted(false);
    }
}
void Canvas::dragMoveEvent(QGraphicsSceneDragDropEvent * event)
{
    if(event->mimeData()->property("acceptable").toBool())
    {
        event->acceptProposedAction();
    }
    else
    {
        event->setAccepted(false);
    }
}

void Canvas::dragLeaveEvent(QGraphicsSceneDragDropEvent * event)
{
    if(event->mimeData()->property("acceptable").toBool())
    {
        event->acceptProposedAction();
    }
    else
    {
        event->setAccepted(false);
    }
}

} // namespace Logicsim

