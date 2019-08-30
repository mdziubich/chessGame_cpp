#include "pawnfield.h"
#include "boardfield.h"
#include "boardposition.h"
#include "gameview.h"
#include "utils.h"

extern GameView *game;

PawnField::PawnField(BoardPosition position,
                     QString imagePath,
                     QGraphicsItem *parent): QGraphicsRectItem(parent) {
    this->position = position;

    setPen(Qt::NoPen);
    Utils::setImage(imagePath, this);
}

void PawnField::setPosition(BoardPosition position) {
    this->position = position;
}

BoardPosition PawnField::getPosition() {
    return position;
}
