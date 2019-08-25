#ifndef BOARDFIELD_H
#define BOARDFIELD_H

#include <QGraphicsPolygonItem>

class BoardField: public QGraphicsPolygonItem {
public:
    BoardField();

    static int defaultHeight;
};

#endif // BOARDFIELD_H
