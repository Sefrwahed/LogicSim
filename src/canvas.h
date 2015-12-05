#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsView>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneMouseEvent>
#include <QMimeData>

namespace Logicsim
{

class Canvas : public QGraphicsScene
{
    Q_OBJECT

public:
    Canvas(QObject *parent = 0);
    ~Canvas();

    QGraphicsView* view();

    int tabIndex() const;
    void setTabIndex(int index);

protected:
    void dropEvent(QGraphicsSceneDragDropEvent * event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent * event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent * event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent * event);

public Q_SLOTS:
    bool tabAboutToBeClosed(int index);

private:
    class Private;
    Private* const d;
};

} // namespace Logicsim

#endif // CANVAS_H
