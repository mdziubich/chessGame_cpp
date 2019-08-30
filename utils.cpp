#include "utils.h"
#include <QBrush>

void Utils::setBackgroundColor(QColor color, QAbstractGraphicsShapeItem *item) {
    QBrush brush;
    brush.setStyle((Qt::SolidPattern));
    brush.setColor(color);
    item->setBrush(brush);
}
