#include "boardfield.h"
#include <utils.h>
#include <gameview.h>

int BoardField::defaultWidthHeight = 60;

extern GameView *game;

BoardField::BoardField(QColor backgroundColor,
                       BoardPosition position,
                       QGraphicsItem *parent): QGraphicsRectItem(parent) {
    this->position = position;

    Utils::setBackgroundColor(backgroundColor, this);
    setPen(Qt::NoPen);
    setAcceptHoverEvents(true);
}

BoardPosition BoardField::getPosition() {
    return position;
}
