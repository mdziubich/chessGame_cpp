#include "queenpawnmodel.h"

QueenPawnModel::QueenPawnModel(BoardPosition position, PlayerType owner, PawnType type, QString imagePath): BasePawnModel (position, owner, type, imagePath) {}

bool QueenPawnModel::validateMove(BoardPosition positionToMove, BasePawnModel *pawnOnPositionToMove, BoardPosition *requestedActivePawnPosition) {
    if (pawnOnPositionToMove && pawnOnPositionToMove->owner == this->owner) {
        return false;
    }

    if (validateDiagonalMove(positionToMove, pawnOnPositionToMove)) {
        return true;
    }

    return validateVerticalOrHorizontalMove(positionToMove, pawnOnPositionToMove);
}
