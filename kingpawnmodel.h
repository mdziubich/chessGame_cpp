#ifndef KINGPAWNMODEL_H
#define KINGPAWNMODEL_H

#include "basepawnmodel.h"

class KingPawnModel: public BasePawnModel {

public:
    KingPawnModel(BoardPosition position, PlayerType owner, PawnType type, QString imagePath);

    bool validateMove(BoardPosition positionToMove, BasePawnModel *pawnOnPositionToMove, BoardPosition *requestedActivePawnPosition);
};

#endif // KINGPAWNMODEL_H
