#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsView>

namespace Logicsim
{

class Canvas : public QGraphicsScene
{
    Q_OBJECT

public:
    Canvas(QObject *parent = 0);
    ~Canvas();

    QGraphicsView* view();

    void setTabIndex(int index);

public Q_SLOTS:
    void tabAboutToBeClosed(int index);

Q_SIGNALS:
    void confirmTabClose(int index);

private:
    class Private;
    Private* const d;
};

} // namespace Logicsim

#endif // CANVAS_H
