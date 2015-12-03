#include "canvas.h"

// Qt includes
#include <QDebug>
#include <QMessageBox>

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
    event->acceptProposedAction();
    qDebug() << "I am dropped ";

}
void Canvas::dragEnterEvent(QGraphicsSceneDragDropEvent * event)
{

    event->acceptProposedAction();
    qDebug() << "I am dragged ";


}
void Canvas::dragMoveEvent(QGraphicsSceneDragDropEvent * event)
{
    event->acceptProposedAction();
}

void Canvas::dragLeaveEvent(QGraphicsSceneDragDropEvent * event)
{
    event->acceptProposedAction();
    qDebug() << "I am leaved ";

}

} // namespace Logicsim
