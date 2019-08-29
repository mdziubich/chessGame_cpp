#include "boardfield.h"
#include <utils.h>
#include <gameview.h>

int BoardField::defaultWidthHeight = 60;

extern GameView *game;

BoardField::BoardField(Qt::GlobalColor backgroundColor,
                       BoardPosition position,
                       QGraphicsItem *parent): QGraphicsRectItem(parent) {
    this->position = position;
    isPlaced = false; //TODO: initialize properly this value

    Utils::setBackgroundColor(backgroundColor, this);
    setAcceptHoverEvents(true);
}

BoardPosition BoardField::getPosition() {
    return position;
}
