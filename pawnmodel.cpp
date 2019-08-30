#include "pawnmodel.h"

PawnModel::PawnModel(BoardPosition position, PlayerType owner, PawnType type, QString imagePath) {
    this->position = position;
    this->owner = owner;
    this->type = type;
    this->imagePath = imagePath;
    didTakeFirstMove = false;
}
