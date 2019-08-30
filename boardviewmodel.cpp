#include "boardviewmodel.h"
#include "boardview.h"
#include "boardfield.h"
#include <math.h>

BoardViewModel::BoardViewModel() {
    activePawn = nullptr;
    whosTurn = PlayerType::black;
    isEnPassantAvailable = false;
    pawnViewModel = PawnViewModel();

    initializePawns();
}

QList<PawnModel*> BoardViewModel::getBlackPawns() {
    return blackPawns;
}

QList<PawnModel*> BoardViewModel::getWhitePawns() {
    return whitePawns;
}

PawnModel* BoardViewModel::getActivePawn() {
    return activePawn;
}

void BoardViewModel::setActivePawnForField(PawnField *pawn) {
    PawnModel* pawnModel = getPawnOnBoardPosition(pawn->getPosition());

    if (pawnModel && pawnModel->owner == whosTurn) {
        activePawn = pawnModel;
        pawn->setZValue(1);
    }
}

void BoardViewModel::setNewPositionForActivePawn(BoardPosition position) {
    activePawn->position = position;
}

void BoardViewModel::discardActivePawn() {
    activePawn = nullptr;
}

PawnModel* BoardViewModel::getPawnOnBoardPosition(BoardPosition baordPosition) {
    for (int i = 0; i < blackPawns.length(); i++) {
        PawnModel *pawnModel = blackPawns[i];
        if (baordPosition.x == pawnModel->position.x &&
                baordPosition.y == pawnModel->position.y) {
            return pawnModel;
        }
    }

    for (int i = 0; i < whitePawns.length(); i++) {
        PawnModel *pawnModel = whitePawns[i];
        if (baordPosition.x == pawnModel->position.x &&
                baordPosition.y == pawnModel->position.y) {
            return pawnModel;
        }
    }

    return nullptr;
}

bool BoardViewModel::validatePawnPalcementForMousePosition(QPoint point) {
    if (point.x() > BoardView::startXPosition &&
            point.x() < (BoardView::startXPosition + BoardField::defaultWidthHeight*BoardView::numberOfRowsColumns) &&
            point.y() > BoardView::startYPosition &&
            point.y() < (BoardView::startYPosition + BoardField::defaultWidthHeight*BoardView::numberOfRowsColumns)) {
        return true;
    }
    return false;
}

bool BoardViewModel::validatePawnMove(BoardPosition positionToMove) {
    switch (activePawn->type) {
    case PawnType::king:
        return validateKingPawnMove(positionToMove);
    case PawnType::queen:
        return validateQueenPawnMove(positionToMove);
    case PawnType::rook:
        return validateRookPawnMove(positionToMove);
    case PawnType::bishop:
        return validateBishopPawnMove(positionToMove);
    case PawnType::knight:
        return validateKnightPawnMove(positionToMove);
    case PawnType::pawn:
        return validateBasePawnMove(positionToMove);
    }
}

void BoardViewModel::switchRound() {
    switch (whosTurn) {
    case PlayerType::black:
        whosTurn = PlayerType::white;
        break;
    case PlayerType::white:
        whosTurn = PlayerType::black;
        break;
    }
}

BoardPosition BoardViewModel::getBoardPositionForMousePosition(QPoint point) {
    int xPosition = static_cast<int>(floor((point.x() - BoardView::startXPosition)/BoardField::defaultWidthHeight));
    int yPosition = static_cast<int>(floor((point.y() - BoardView::startYPosition)/BoardField::defaultWidthHeight));

    return BoardPosition { xPosition, yPosition };
}

void BoardViewModel::initializePawns() {
    initializePawnsForRow(0, PlayerType::black);
    initializePawnsForRow(1, PlayerType::black);
    initializePawnsForRow(6, PlayerType::white);
    initializePawnsForRow(7, PlayerType::white);
}

void BoardViewModel::initializePawnsForRow(int rowNumber, PlayerType owner) {
    for (int i = 0; i < BoardView::numberOfRowsColumns; i++) {
        BoardPosition boardPosition = { i, rowNumber };
        PawnType type = pawnViewModel.getTypeForInitialPosition(boardPosition);
        QString imagePath = pawnViewModel.getImagePath(type, owner);
        PawnModel *pawn = new PawnModel(boardPosition, owner, type, imagePath);

        switch (owner) {
        case PlayerType::black:
            blackPawns.append(pawn);
            break;
        case PlayerType::white:
            whitePawns.append(pawn);
            break;
        }
    }
}

bool BoardViewModel::shouldReplaceActivePawnWithQueen() {
    return false;
}

bool BoardViewModel::validateKingPawnMove(BoardPosition positionToMove) {
    PawnModel *pawn = getPawnOnBoardPosition(positionToMove);

    if (pawn && pawn->owner == whosTurn) {
        return false;
    }

    return false;
}

bool BoardViewModel::validateQueenPawnMove(BoardPosition positionToMove) {
    PawnModel *pawn = getPawnOnBoardPosition(positionToMove);

    if (pawn && pawn->owner == whosTurn) {
        return false;
    }

    return false;
}

bool BoardViewModel::validateRookPawnMove(BoardPosition positionToMove) {
    PawnModel *pawn = getPawnOnBoardPosition(positionToMove);

    if (pawn && pawn->owner == whosTurn) {
        return false;
    }

    return false;
}

bool BoardViewModel::validateBishopPawnMove(BoardPosition positionToMove) {
    PawnModel *pawn = getPawnOnBoardPosition(positionToMove);

    if (pawn && pawn->owner == whosTurn) {
        return false;
    }

    int xDiference = positionToMove.x - activePawn->position.x;
    int yDiference = positionToMove.y - activePawn->position.y;

    if (abs(xDiference) != abs(yDiference)) {
        return false;
    }

    if (abs(xDiference) == 1) {
        return true;
    }

    for (int i = 1; i < abs(xDiference); i++) {
        BoardPosition positionToCheck;

        if (xDiference < 0) {
            if (yDiference < activePawn->position.y) {
                positionToCheck = { activePawn->position.x + (xDiference + i), activePawn->position.y + (yDiference + i) };
            } else {
                positionToCheck = { activePawn->position.x + (xDiference + i), activePawn->position.y + (yDiference - i) };
            }
        } else if (yDiference < 0) {
            positionToCheck = { activePawn->position.x + (xDiference - i), activePawn->position.y + (yDiference + i) };
        } else {
            positionToCheck = { activePawn->position.x + (xDiference - i), activePawn->position.y + (yDiference - i) };
        }

        PawnModel *pawnToCheck = getPawnOnBoardPosition(positionToCheck);

        if (pawnToCheck) {
            return false;
        }
    }

    return true;
}

bool BoardViewModel::validateKnightPawnMove(BoardPosition positionToMove) {
    PawnModel *pawn = getPawnOnBoardPosition(positionToMove);

    if (pawn && pawn->owner == whosTurn) {
        return false;
    }

    int xDiference = abs(positionToMove.x - activePawn->position.x);
    int yDiference = abs(positionToMove.y - activePawn->position.y);

    if (xDiference == 2 && yDiference == 1) {
        return true;
    }

    if (xDiference == 1 && yDiference == 2) {
        return true;
    }

    return false;
}

bool BoardViewModel::validateBasePawnMove(BoardPosition positionToMove) {
    PawnModel *pawn = getPawnOnBoardPosition(positionToMove);

    if (pawn && pawn->owner == whosTurn) {
        return false;
    }

    // pawns cannot move backwards
    // Normally a pawn moves by advancing a single square, but the first time a pawn moves, it has the option of advancing two squares
    // Pawns may not use the initial two-square advance to jump over an occupied square, or to capture
    // Any piece immediately in front of a pawn, friend or foe, blocks its advance

    /*
    En passant capture. It can occur after a pawn advances two squares using its initial two-step move option,
    and the square passed over is attacked by an enemy pawn.
    The enemy pawn is entitled to capture the moved pawn "in passing" – as if it had advanced only one square.
    The capturing pawn moves to the square over which the moved pawn passed, and the moved pawn is removed from the board.
    The option to capture the moved pawn en passant must be exercised on the move immediately following the double-step pawn advance,
    or it is lost for the remainder of the game.
    */
    return true;
}

bool BoardViewModel::isFieldOccupiedByEnemy(BoardPosition fieldPosition) {
    return false;
}