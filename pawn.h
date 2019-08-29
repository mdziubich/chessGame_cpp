#ifndef PAWN_H
#define PAWN_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <boardposition.h>

enum class PawnType {
    king,
    queen,
    rook,
    bishop,
    knight,
    pawn
};

enum class PlayerType {
    playerOne,
    playerTwo
};

class Pawn: public QGraphicsRectItem {

public:
    Pawn(BoardPosition position, QGraphicsItem *parent = nullptr);

    PlayerType owner;

    void setPosition(BoardPosition position);
    BoardPosition getPosition();
private:
    BoardPosition position;

    void setInitialImage();
    QString getImagePath(PawnType type, PlayerType player);
    PawnType getTypeForInitialPosition(BoardPosition position);
    PlayerType getPlayerForInitialPosition(BoardPosition position);
};

#endif // PAWN_H
