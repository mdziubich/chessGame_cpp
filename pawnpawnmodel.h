#ifndef PAWNPAWNMODEL_H
#define PAWNPAWNMODEL_H

#include "basepawnmodel.h"

class PawnPawnModel: public BasePawnModel {

public:
    PawnPawnModel(BoardPosition position, PlayerType owner, PawnType type, QString imagePath);

    bool validateMove(BoardPosition positionToMove, BasePawnModel *pawnOnPositionToMove, BoardPosition *requestedActivePawnPosition);
};

#endif // PAWNPAWNMODEL_H
