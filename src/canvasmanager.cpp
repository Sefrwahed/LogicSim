#include "canvasmanager.h"

// Qt includes

#include <QtMath>

// Local includes

#include "component.h"

namespace Logicsim
{

class CanvasManager::Private
{
public:
    Private() :
        componentCount(0),
        selectedComponentIndex(-1),
        selectedLineIndex(-1),
        componentId(0),
        oldSquareNumberOfMovingComponent(0),
        selectedComponent(0),
        canvas(0),
        selectedInput(0),
        selectedOutput(0),
        selectedLine(0)
    {}

    int                    componentCount;
    int                    selectedComponentIndex;
    int                    selectedLineIndex;
    int                    componentId;
    int                    oldSquareNumberOfMovingComponent;
    Component*             selectedComponent;
    QGraphicsScene*        canvas;
    Pin*                   selectedInput;
    Pin*                   selectedOutput;
    ConnectionLine*        selectedLine;
    Cell                   oldCellOfMovingComponent;
    QSet<qint32>           acquiredSquares;
    QList<Component *>     mComponents;
    QList<ConnectionLine*> connectionLines;
    QString                associatedFileName;
};

CanvasManager::CanvasManager(QObject *parent, QGraphicsScene *canvas)
    : QObject(parent), d(new Private)
{
    d->canvas = canvas;
}

QList<Component *> CanvasManager::components()
{
    return d->mComponents;
}

Component *CanvasManager::componentById(quint32 id)
{
    foreach (Component* c, d->mComponents)
    {
        if(c->uniqueId() == id)
                return c;
    }
    return 0;
}

void CanvasManager::setComponents(QList<Component *> clist)
{
    d->mComponents = clist;
}

QGraphicsScene *CanvasManager::canvas()
{
    return d->canvas;
}

void CanvasManager::setCanvas(QGraphicsScene *s)
{
    d->canvas = s;
}

int CanvasManager::selectedComponentIndex()
{
    return d->selectedComponentIndex;
}

int CanvasManager::selectedLineIndex()
{
    return d->selectedLineIndex;
}

void CanvasManager::addComponent(Component *component, QPointF scenePos)
{
    Cell c = findSuitableCell(scenePos);
    if (!c.isNull())
    {
        parkComponent(component, c);
        int squareNumber = calculateSquareNumber(c);
        d->acquiredSquares.insert(squareNumber);
        component->setUniqueId(d->componentId++);
        component->setName("Component " + QString::number(component->uniqueId()));
        d->canvas->addItem(component);
        d->componentCount++;
        d->mComponents << component;
        emit componentAdded(d->componentCount - 1);
    }
}

void CanvasManager::selectComponent(Component *component)
{
    if(d->selectedComponent != component)
    {
        unSelectPins();
        qDebug() << "selected: " << component->name();
        d->selectedComponent = component;
        d->selectedComponentIndex = d->mComponents.indexOf(d->selectedComponent);
        d->selectedComponent->setSelection(true);
        emit componentSelectedFromCanvas(d->mComponents.indexOf(d->selectedComponent));
    }
}

void CanvasManager::unSelectComponent()
{
    if(d->selectedComponent != 0)
    {
        qDebug() << "Unselected: " << d->selectedComponent->name();
        d->selectedComponentIndex = -1;
        d->selectedComponent->setSelection(false);
        d->selectedComponent = 0;
    }
}

void CanvasManager::deleteComponent(int index)
{
    unSelectComponent();
    Component* c = d->mComponents.at(index);
    d->canvas->removeItem(c);
    d->acquiredSquares.remove(selectedComponentSquare(index));
    d->mComponents.removeAt(index);
    d->componentCount--;

    foreach(Pin* p, c->pins())
    {
        foreach(ConnectionLine* l, p->connectedLines())
        {
            emit l->lineSelected();
            deleteLine(d->selectedLineIndex);
        }
    }

    emit componentDeleted(index);
    delete c;
}

void CanvasManager::movingComponent(Component *component)
{
    if (d->oldSquareNumberOfMovingComponent != 0)
        return;

    qreal x = component->pos().x() + component->boundingRect().width()/2;
    qreal y = component->pos().y() + component->boundingRect().height()/2;

    int col = ((x - GRID_STEP/2) / GRID_STEP) + 1;
    int row = ((y - GRID_STEP/2) / GRID_STEP) + 1;

    d->oldCellOfMovingComponent.setCol(col);
    d->oldCellOfMovingComponent.setRow(row);
    d->oldSquareNumberOfMovingComponent = calculateSquareNumber(d->oldCellOfMovingComponent);
}

void CanvasManager::componentMoved(Component* component, QPointF scenePos)
{
    Cell newCell = findSuitableCell(scenePos);
    if(!newCell.isNull() &&
       calculateSquareNumber(newCell) != d->oldSquareNumberOfMovingComponent &&
       scenePos.x() > 0 && scenePos.y() > 0 &&
       scenePos.x() < CANVAS_WIDTH && scenePos.y() < CANVAS_HEIGHT)
    {
        qDebug() << "Gate Moved";
        parkComponent(component, newCell);
        d->acquiredSquares.remove(d->oldSquareNumberOfMovingComponent);
        d->acquiredSquares.insert(calculateSquareNumber(newCell));
    }
    else
    {
        qDebug() << "Gate Not Moved";
        parkComponent(component, d->oldCellOfMovingComponent);
    }

    d->oldCellOfMovingComponent.erase();
    d->oldSquareNumberOfMovingComponent = 0;
}

void CanvasManager::addLineToCanvas(ConnectionLine* line)
{
    line->setZValue(-1);

    connect(line, SIGNAL(lineSelected()),
            this, SLOT(selectLine()));

    d->canvas->addItem(line);

    unSelectPins();
}

void CanvasManager::pinPressed(Pin *p)
{
    if(d->selectedOutput && p->parentComponent() == d->selectedOutput->parentComponent())
    {
        d->selectedOutput = 0;
    }
    else if(d->selectedInput && p->parentComponent() == d->selectedInput->parentComponent())
    {
        d->selectedInput = 0;
    }

    if(p->type() == Pin::Input)
    {
        if(p->isConnected())
        {
            d->selectedOutput = 0;
            return;
        }

        qDebug() << "Disconnected Input pin was clicked";
        d->selectedInput = p;
    }
    else
    {
        qDebug() << "Output pin was clicked";
        d->selectedOutput = p;
    }

    if(d->selectedInput && d->selectedOutput
            && d->selectedInput->parentComponent() != d->selectedOutput->parentComponent())
    {
        ConnectionLine* line = new ConnectionLine(d->selectedOutput, d->selectedInput);
        d->selectedInput->setConnected(line);
        d->selectedOutput->setConnected(line);
        d->connectionLines << line;
        addLineToCanvas(line);
    }
    qDebug() << "Selected input: " << d->selectedInput;
    qDebug() << "Selected output: " << d->selectedOutput;
}

void CanvasManager::unSelectPins()
{
    if(d->selectedInput != 0)
    {
        d->selectedInput->setSelected(false);
        d->selectedInput = 0;
    }
    if(d->selectedOutput != 0)
    {
        d->selectedOutput->setSelected(false);
        d->selectedOutput = 0;
    }
}

Cell CanvasManager::findSuitableCell(QPointF scenePos)
{
    int col = qCeil(scenePos.x() / GRID_STEP);
    int row = qCeil(scenePos.y() / GRID_STEP);
    Cell c(col, row);
    int squareNumber = calculateSquareNumber(c);

    if (d->acquiredSquares.contains(squareNumber) && squareNumber != d->oldSquareNumberOfMovingComponent)
    {
        foreach(Cell i, alternativePlaces(c))
        {
            int alternativeSquareNumber = calculateSquareNumber(i);

            if(!d->acquiredSquares.contains(alternativeSquareNumber))
            {
                squareNumber = alternativeSquareNumber;

                return i;
            }
        }
    }
    else
    {
        return c;
    }

    return Cell();
}

void CanvasManager::parkComponent(Component * component, Cell c)
{
    qreal x = (c.col() - 1) * GRID_STEP + GRID_STEP/2;
    qreal y = (c.row() - 1) * GRID_STEP + GRID_STEP/2;

    component->setPos(x - component->boundingRect().width()/2,
              y - component->boundingRect().height()/2);
    component->updateConnection();
}

QList<Cell> CanvasManager::alternativePlaces(Cell c) const
{
    QList<Cell> cells;
    int col = c.col();
    int row = c.row();

    if(col - 1 >= 1)
    {
        cells << Cell(col - 1, row);
    }

    if(col + 1 <= NUMBER_OF_SQUARES_IN_ROW)
    {
        cells << Cell(col + 1, row);
    }

    if(row - 1 >= 1)
    {
        cells << Cell(col, row - 1);

        if(col - 1 >= 1)
            cells << Cell(col - 1, row - 1);

        if(col + 1 <= NUMBER_OF_SQUARES_IN_ROW)
            cells << Cell(col + 1, row - 1);
    }

    if(row + 1 <= NUMBER_OF_SQUARES_IN_COLUMN)
    {
        cells << Cell(col, row + 1);

        if(col - 1 >= 1)
            cells << Cell(col - 1, row + 1);

        if(col + 1 <= NUMBER_OF_SQUARES_IN_ROW)
            cells << Cell(col + 1, row + 1);
    }

    return cells;
}

int CanvasManager::calculateSquareNumber(Cell c) const
{
    return c.col() + ((c.row() - 1) * NUMBER_OF_SQUARES_IN_ROW);
}

int CanvasManager::selectedComponentSquare(int index) const
{
    QPointF position = d->mComponents.at(index)->pos();
    int col = qCeil(position.x() / GRID_STEP);
    int row = qCeil(position.y() / GRID_STEP);
    Cell c(col, row);
    return calculateSquareNumber(c);
}

void CanvasManager::selectedFromWorkspace(int index)
{
    unSelectComponent();
    selectComponent(d->mComponents.at(index));
}

void CanvasManager::renameComponent(QTableWidgetItem *item)
{
    if(item->row() < d->componentCount)
    {
        d->mComponents.at(item->row())->setName(item->text());
    }
}

void CanvasManager::selectLine()
{
    unSelectComponent();
    d->selectedLine = static_cast<ConnectionLine*>(sender());
    d->selectedLineIndex = d->connectionLines.indexOf(d->selectedLine);
}

void CanvasManager::unSelectLine()
{
    if(d->selectedLine != 0)
    {
        d->selectedLine->setSelected(false);
        d->selectedLine = 0;
        d->selectedLineIndex = -1;
    }
}

void CanvasManager::deleteLine(int index)
{
    unSelectLine();
    ConnectionLine* l = d->connectionLines.at(index);
    emit l->lineDeleted();
    d->canvas->removeItem(l);
    d->connectionLines.removeAt(index);
    delete l;
}

void CanvasManager::pushDataToStream(QDataStream &stream)
{
    QList<qint32> acquiredSquares;

    foreach (qint32 s, d->acquiredSquares)
    {
        acquiredSquares << s;
    }

    stream << acquiredSquares << d->mComponents;
    foreach (ConnectionLine* cl, d->connectionLines)
    {
        stream << cl->output()->parentComponent()->uniqueId()
               << cl->input()->parentComponent()->uniqueId()
               <<cl->input()->number();
    }
}

void CanvasManager::loadDataFromStream(QDataStream &stream)
{
    QList<quint32> squaresList;
    stream >> squaresList >> d->mComponents ;

    d->componentId = d->mComponents.last()->uniqueId() + 1;

    while (!stream.atEnd())
    {
        quint32 outputPinParentComponentId, inputPinParentComponentId, inputPinNumber;
        stream >> outputPinParentComponentId >> inputPinParentComponentId >> inputPinNumber;

        Component * outPinParentComp = componentById(outputPinParentComponentId);
        Component * inPinParentComp =  componentById(inputPinParentComponentId);

        // Output pin always comes first in the list then comes the input pins
        ConnectionLine* cl = new ConnectionLine(outPinParentComp->pins().at(0),
                                                inPinParentComp->pins().at(inputPinNumber));
        outPinParentComp->pins().at(0)->setConnected(cl);
        inPinParentComp->pins().at(inputPinNumber)->setConnected(cl);
        d->connectionLines << cl;
    }

    foreach(qint32 s, squaresList)
    {
        d->acquiredSquares.insert(s);
    }
}

void CanvasManager::populateLoadedComponents()
{
    foreach(Component* c, d->mComponents)
    {
        d->canvas->addItem(c);
        emit componentAdded(d->componentCount++);
    }

    foreach (ConnectionLine* l, d->connectionLines)
    {
        addLineToCanvas(l);
    }
}

QString CanvasManager::associatedFileName() const
{
    return d->associatedFileName;
}

void CanvasManager::setAssociatedFileName(QString &filename)
{
    d->associatedFileName = filename;
}

CanvasManager::~CanvasManager()
{
    delete d;
}

QDataStream &operator<<(QDataStream &out, CanvasManager * cm)
{
    cm->pushDataToStream(out);
    return out;
}

QDataStream &operator>>(QDataStream &in, CanvasManager *& cm)
{
    cm = new CanvasManager();
    cm->loadDataFromStream(in);

    return in;
}

} // namespace Logicsim
