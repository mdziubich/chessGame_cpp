#ifndef BOARDFIELD_H
#define BOARDFIELD_H

#include <QGraphicsPolygonItem>
#include <boardposition.h>

class BoardField: public QGraphicsPolygonItem {
public:
    BoardField(Qt::GlobalColor backgroundColor, BoardPosition position);

    static int defaultHeight;

    BoardPosition position;
};

#endif // BOARDFIELD_H
