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

    qreal round(qreal val, int step)
    {
       int tmp = int(val) + step /2;
       tmp -= tmp % step;
       return qreal(tmp);
    }

    int            tabIndex;
    QGraphicsView* view;
    CanvasManager *mCanvasManager;
};

Canvas::Canvas(QObject *parent)
    : QGraphicsScene(parent), d(new Private)
{
    d->view = new QGraphicsView(this);
    d->view->setSceneRect(0,0,CANVAS_WIDTH,CANVAS_HEIGHT);

    d->mCanvasManager = new CanvasManager(parent, this);
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

CanvasManager *Canvas::canvasManager()
{
    return d->mCanvasManager;
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

        Component* component = static_cast<Component*>(QMetaType::create(typeId));
        d->mCanvasManager->addComponent(component, event->scenePos());
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

void Canvas::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(mouseGrabberItem() != 0)
    {
        Component *component = dynamic_cast<Component*>(mouseGrabberItem());
        if(component)
        {
            d->mCanvasManager->selectComponent(component);
            d->mCanvasManager->movingComponent(component);
            d->mCanvasManager->componentMoved(component, event->scenePos());
        }
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

void Canvas::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Delete:
        if(d->mCanvasManager->selectedComponentIndex() != -1)
        {
            qDebug() << "Delete";
            d->mCanvasManager->deleteComponent(d->mCanvasManager->selectedComponentIndex());
        }
        break;
    }
}

void Canvas::drawBackground(QPainter *painter, const QRectF &rect)
{
    int step = GRID_STEP;
    painter->setPen(QPen(QColor(200, 200, 255, 125)));

    // draw horizontal grid
    qreal start = d->round(rect.top(), step);
    if (start > rect.top()) {
        start -= step;
    }

    for (qreal y = start - step; y < rect.bottom(); ) {
        y += step;
        painter->drawLine(rect.left(), y, rect.right(), y);
    }

    // now draw vertical grid
    start = d->round(rect.left(), step);
    if (start > rect.left()) {
        start -= step;
    }

    for (qreal x = start - step; x < rect.right(); ) {
        x += step;
        painter->drawLine(x, rect.top(), x, rect.bottom());
    }
}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
    d->mCanvasManager->unSelectComponent();
    Canvas::mouseMoveEvent(event);
}

void Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(mouseGrabberItem() != 0)
    {
        Component *component = dynamic_cast<Component*>(mouseGrabberItem());
        qDebug()<< component;
        qDebug() << mouseGrabberItem();
        if(component)
        {
            d->mCanvasManager->selectComponent(component);
            d->mCanvasManager->movingComponent(component);
        }
    }
    QGraphicsScene::mouseMoveEvent(event);
}

} // namespace Logicsim

