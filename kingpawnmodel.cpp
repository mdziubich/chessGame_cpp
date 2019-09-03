#include "kingpawnmodel.h"

KingPawnModel::KingPawnModel(BoardPosition position, PlayerType owner, PawnType type, QString imagePath): BasePawnModel(position, owner, type, imagePath) {}

bool KingPawnModel::validateMove(BoardPosition positionToMove, BasePawnModel *pawnOnPositionToMove, BoardPosition *requestedActivePawnPosition) {
    if (pawnOnPositionToMove && pawnOnPositionToMove->owner == this->owner) {
        return false;
    }

    return pawnWantsToMoveByOneField(positionToMove);
}
