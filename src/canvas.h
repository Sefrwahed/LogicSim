#ifndef CANVAS_H
#define CANVAS_H

// Qt includes
#include <QTableWidgetItem>
#include <QGraphicsView>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneMouseEvent>
#include <QMimeData>
#include <QKeyEvent>

// Local includes
#include "pin.h"
#include "gates.h"
#include "componentstab.h"
#include "canvasmanager.h"

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

    CanvasManager *canvasManager();
    void setManager(CanvasManager* manager);

protected:
    void dropEvent(QGraphicsSceneDragDropEvent * event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent * event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent * event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent * event);

    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);

    void keyPressEvent(QKeyEvent *event);

    void drawBackground(QPainter *painter, const QRectF &rect);

public Q_SLOTS:
    void tabAboutToBeClosed(int index);

Q_SIGNALS:
    void saveCanvasAndClose(int index);
    void closeCanvas(int index);

private:
    class Private;
    Private* const d;
};

} // namespace Logicsim

#endif // CANVAS_H

