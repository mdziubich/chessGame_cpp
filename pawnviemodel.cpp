#include "pawnviewmodel.h"

PawnViewModel::PawnViewModel() {}

QString PawnViewModel::getImagePath(PawnType type, PlayerType owner) {
    QString imageFileName;

    switch (type) {
    case PawnType::king:
        if (owner == PlayerType::black) {
            imageFileName = "king_black.svg";
        } else {
            imageFileName = "king_white.svg";
        }
        break;
    case PawnType::queen:
        if (owner == PlayerType::black) {
            imageFileName = "queen_black.svg";
        } else {
            imageFileName = "queen_white.svg";
        }
        break;
    case PawnType::rook:
        if (owner == PlayerType::black) {
            imageFileName = "rook_black.svg";
        } else {
            imageFileName = "rook_white.svg";
        }
        break;
    case PawnType::bishop:
        if (owner == PlayerType::black) {
            imageFileName = "bishop_black.svg";
        } else {
            imageFileName = "bishop_white.svg";
        }
        break;
    case PawnType::knight:
        if (owner == PlayerType::black) {
            imageFileName = "knight_black.svg";
        } else {
            imageFileName = "knight_white.svg";
        }
        break;
    case PawnType::pawn:
        if (owner == PlayerType::black) {
            imageFileName = "pawn_black.svg";
        } else {
            imageFileName = "pawn_white.svg";
        }
        break;
    }

    return ":Images/" + imageFileName;
}

PawnType PawnViewModel::getTypeForInitialPosition(BoardPosition position) {
    if (position.y == 1 || position.y == 6) {
        return PawnType::pawn;
    }

    switch (position.x) {
    case 0:
    case 7:
        return PawnType::rook;
    case 1:
    case 6:
        return PawnType::knight;
    case 2:
    case 5:
        return PawnType::bishop;
    case 3:
        return PawnType::queen;
    case 4:
        return PawnType::king;
    }

    return PawnType::pawn;
}
