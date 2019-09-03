#ifndef PAWN_H
#define PAWN_H

#include <QGraphicsRectItem>
#include <QLabel>
#include "boardposition.h"
#include "basepawnmodel.h"

class PawnField: public QGraphicsRectItem {

public:
    PawnField(BoardPosition position,
              QString imagePath,
              QGraphicsItem *parent = nullptr);

    BoardPosition getPosition();
    void setPosition(BoardPosition position);
    void setImage(QString imagePath);

private:
    BoardPosition position;
    QLabel *imageLabel;
    QPixmap image;
};

#endif // PAWN_H
