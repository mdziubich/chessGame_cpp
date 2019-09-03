#include "pawnpawnmodel.h"

PawnPawnModel::PawnPawnModel(BoardPosition position, PlayerType owner, PawnType type, QString imagePath): BasePawnModel (position, owner, type, imagePath) {}

/*
    Pawns cannot move backwards.
    Normally a pawn moves by advancing a single square, but the first time a pawn moves, it has the option of advancing two squares
    Pawns may not use the initial two-square advance to jump over an occupied square, or to capture
    Any piece immediately in front of a pawn, friend or foe, blocks its advance
*/
bool PawnPawnModel::validateMove(BoardPosition positionToMove, BasePawnModel *pawnOnPositionToMove, BoardPosition *requestedActivePawnPosition) {
    if (pawnOnPositionToMove && pawnOnPositionToMove->owner == this->owner) {
        return false;
    }

    int xDiference = positionToMove.x - this->position.x;
    int yDiference = positionToMove.y - this->position.y;
    int numbeOfFieldsToMove = std::max(abs(xDiference), abs(yDiference));

    bool wantsToMoveByOneField = (numbeOfFieldsToMove == 1);

    if (abs(xDiference) > 1 || abs(yDiference) > 2) {
        return false;
    }

    if ( !wantsToMoveByOneField && this->didTakeFirstMove) {
        return false;
    }

    bool wantsToMoveInGoodDirection;

    switch (this->owner) {
    case PlayerType::black:
        wantsToMoveInGoodDirection = yDiference > 0;
        break;
    case PlayerType::white:
        wantsToMoveInGoodDirection = yDiference < 0;
        break;
    }

    if (wantsToMoveByOneField) {
        if (requestedActivePawnPosition && xDiference == 0)  {
            return (wantsToMoveInGoodDirection &&
                    requestedActivePawnPosition->x != positionToMove.x &&
                    requestedActivePawnPosition->y != positionToMove.y);
        } else if (xDiference == 0) {
            return (wantsToMoveInGoodDirection && !pawnOnPositionToMove);
        } else if (requestedActivePawnPosition) {
            return (wantsToMoveInGoodDirection &&
                    requestedActivePawnPosition->x == positionToMove.x &&
                    requestedActivePawnPosition->y == positionToMove.y) || (wantsToMoveInGoodDirection && pawnOnPositionToMove);
        } else {
            return (wantsToMoveInGoodDirection && pawnOnPositionToMove);
        }
    }

    return (wantsToMoveInGoodDirection &&
            !this->didTakeFirstMove &&
            xDiference == 0);
}
