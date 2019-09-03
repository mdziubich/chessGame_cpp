#include "basepawnmodel.h"

BasePawnModel::BasePawnModel(BoardPosition position, PlayerType owner, PawnType type, QString imagePath) {
    this->position = position;
    this->owner = owner;
    this->type = type;
    this->imagePath = imagePath;
    didTakeFirstMove = false;
}

bool BasePawnModel::pawnWantsToMoveByOneField(BoardPosition positionToMove) {
    int xDiference = positionToMove.x - this->position.x;
    int yDiference = positionToMove.y - this->position.y;
    int numbeOfFieldsToMove = std::max(abs(xDiference), abs(yDiference));

    return (numbeOfFieldsToMove == 1);
}

bool BasePawnModel::validateDiagonalMove(BoardPosition positionToMove, BasePawnModel *pawnOnPositionToMove) {
    if (pawnOnPositionToMove && pawnOnPositionToMove->owner == this->owner) {
        return false;
    }

    int xDiference = positionToMove.x - this->position.x;
    int yDiference = positionToMove.y - this->position.y;

    if (abs(xDiference) != abs(yDiference)) {
        return false;
    }

    return true;
}

bool BasePawnModel::validateVerticalOrHorizontalMove(BoardPosition positionToMove, BasePawnModel *pawnOnPositionToMove) {
    if (pawnOnPositionToMove && pawnOnPositionToMove->owner == this->owner) {
        return false;
    }

    if ((positionToMove.x != this->position.x && positionToMove.y != this->position.y)) {
        return false;
    }

    return true;
}
