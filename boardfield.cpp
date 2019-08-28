#include "boardfield.h"
#include <utils.h>

int BoardField::defaultHeight = 60;

BoardField::BoardField(Qt::GlobalColor backgroundColor, BoardPosition position) {

    this->position = position;

    // points needed to draw square
    QVector<QPointF> points;
    points << QPointF(0, 0)
           << QPointF(defaultHeight, 0)
           << QPointF(defaultHeight, defaultHeight)
           << QPointF(0, defaultHeight);

    // create a polygon
    QPolygonF square(points);
    setPolygon(square);

    Utils::setBackgroundColor(backgroundColor, this);
}
