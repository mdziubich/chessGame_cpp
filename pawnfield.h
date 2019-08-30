#ifndef PAWN_H
#define PAWN_H

#include <QGraphicsRectItem>
#include "boardposition.h"
#include "pawnmodel.h"

class PawnField: public QGraphicsRectItem {

public:
    PawnField(BoardPosition position,
              QString imagePath,
              QGraphicsItem *parent = nullptr);

    BoardPosition getPosition();
    void setPosition(BoardPosition position);
private:
    BoardPosition position;

    void setInitialImage(QString imagePath);
};

#endif // PAWN_H
