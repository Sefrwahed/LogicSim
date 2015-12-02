#include "canvas.h"

// Qt includes
#include <QDebug>

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

void Canvas::setTabIndex(int index)
{
    qDebug() << "I am: " << this << " My new tab index: " << index;
    d->tabIndex = index;
}

void Canvas::tabAboutToBeClosed(int index)
{
    if (index == d->tabIndex)
    {
        // Saving stuff
        emit confirmTabClose(index);
    }
}

} // namespace Logicsim
