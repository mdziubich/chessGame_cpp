#include "boardfield.h"

int BoardField::defaultHeight = 64;

BoardField::BoardField() {

    // points needed to draw square
    QVector<QPointF> points;
    points << QPointF(0, 0)
           << QPointF(defaultHeight, 0)
           << QPointF(defaultHeight, defaultHeight)
           << QPointF(0, defaultHeight);

    // create a polygon
    QPolygonF square(points);
    setPolygon(square);
}
