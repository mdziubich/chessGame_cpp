#ifndef BOARDFIELD_H
#define BOARDFIELD_H

#include <QGraphicsPolygonItem>

class BoardField: public QGraphicsPolygonItem {
public:
    BoardField(Qt::GlobalColor backgroundColor);

    static int defaultHeight;
};

#endif // BOARDFIELD_H
