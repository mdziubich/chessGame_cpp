#ifndef QUEENPAWNMODEL_H
#define QUEENPAWNMODEL_H

#include "basepawnmodel.h"

class QueenPawnModel: public BasePawnModel {

public:
    QueenPawnModel(BoardPosition position, PlayerType owner, PawnType type, QString imagePath);

    bool validateMove(BoardPosition positionToMove, BasePawnModel *pawnOnPositionToMove, BoardPosition *requestedActivePawnPosition);
};

#endif // QUEENPAWNMODEL_H
