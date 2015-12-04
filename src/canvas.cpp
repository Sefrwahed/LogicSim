#include "canvas.h"
#include "drawablegenericgate.h"

#include <QTableWidgetItem>
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
    d->view->setSceneRect(0,0,1500,1500);
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
    if(event->mimeData()->objectName().compare("gate") == 0)
    {
        event->acceptProposedAction();
        double x = event->scenePos().x();
        double y = event->scenePos().y();
        GraphicGate* gate = new GraphicGate(x, y);
        this->addItem(gate);
    }

}
void Canvas::dragEnterEvent(QGraphicsSceneDragDropEvent * event)
{
    if(event->mimeData()->objectName().compare("gate") == 0)
    {
        event->acceptProposedAction();
    }
}
void Canvas::dragMoveEvent(QGraphicsSceneDragDropEvent * event)
{
    if(event->mimeData()->objectName().compare("gate") == 0)
    {
        event->acceptProposedAction();
    }
}

void Canvas::dragLeaveEvent(QGraphicsSceneDragDropEvent * event)
{
    if(event->mimeData()->objectName().compare("gate") == 0)
    {
        event->acceptProposedAction();
    }
}

} // namespace Logicsim
