#ifndef PAWNMODEL_H
#define PAWNMODEL_H

#include <QString>
#include "boardposition.h"

enum class PawnType {
    king,
    queen,
    rook,
    bishop,
    knight,
    pawn
};

enum class PlayerType {
    black,
    white
};

class PawnModel {

public:
    PawnModel(BoardPosition position, PlayerType owner, PawnType type, QString imagePath);

    BoardPosition position;
    PlayerType owner;
    PawnType type;
    QString imagePath;
    bool didTakeFirstMove;
};

#endif // PAWNMODEL_H
