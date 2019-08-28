#include "utils.h"
#include <QBrush>

void Utils::setBackgroundColor(Qt::GlobalColor color, QAbstractGraphicsShapeItem *item) {
    QBrush brush;
    brush.setStyle((Qt::SolidPattern));
    brush.setColor(color);
    item->setBrush(brush);
}
