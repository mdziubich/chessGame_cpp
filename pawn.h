#ifndef PAWN_H
#define PAWN_H

#include <QGraphicsPolygonItem>
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

class Pawn: public QGraphicsPolygonItem {

public:
    Pawn(BoardPosition position);

private:
    BoardPosition position;

    void setInitialImage();
    QString getImagePath(PawnType type, PlayerType player);
    PawnType getTypeForInitialPosition(BoardPosition position);
    PlayerType getPlayerForInitialPosition(BoardPosition position);
};

#endif // PAWN_H
