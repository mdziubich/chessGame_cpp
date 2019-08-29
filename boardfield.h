#ifndef BOARDFIELD_H
#define BOARDFIELD_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <boardposition.h>

class BoardField: public QGraphicsRectItem {
public:
    BoardField(Qt::GlobalColor backgroundColor,
               BoardPosition position,
               QGraphicsItem *parent = nullptr);

    static int defaultWidthHeight;
    bool isPlaced;

    BoardPosition getPosition();

private:
    BoardPosition position;
};

#endif // BOARDFIELD_H
