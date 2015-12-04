#include "componentstab.h"

namespace Logicsim
{

class ComponentsTab::Private
{
public:
    Private() :
        rows(0),
        columns(0)
    {}
    int rows;
    int columns;
};

ComponentsTab::ComponentsTab(QWidget* parent)
    : QTableWidget(parent), d(new Private)
{
}

ComponentsTab::~ComponentsTab()
{
    delete d;
}

QMimeData* ComponentsTab::mimeData(const QList<QTableWidgetItem *> items) const
{
    QMimeData *data = QTableWidget::mimeData(items);
    data->setObjectName("gate");

    return data;
}
}
