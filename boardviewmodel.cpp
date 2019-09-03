#include "boardviewmodel.h"
#include "boardview.h"
#include "boardfield.h"
#include <math.h>

BoardViewModel::BoardViewModel() {
    activePawn = nullptr;
    whosTurn = PlayerType::black;
    isEnPassantAvailable = false;
    pawnViewModel = PawnViewModel();
    winner = nullptr;

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

PlayerType BoardViewModel::getWhosTurn() {
    return whosTurn;
}

PlayerType* BoardViewModel::getWinner() {
    return winner;
}

void BoardViewModel::setActivePawnForField(PawnField *pawn) {
    PawnModel* pawnModel = getPawnOnBoardPosition(pawn->getPosition());

    if (pawnModel && pawnModel->owner == whosTurn) {
        activePawn = pawnModel;
        pawn->setZValue(1);
    }
}

void BoardViewModel::setNewPositionForActivePawn(BoardPosition position) {
    activePawn->didTakeFirstMove = true;
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

bool BoardViewModel::validatePawnMove(BoardPosition positionToMove,
                                      PawnModel *pawn,
                                      BoardPosition *requestedActivePawnPosition) {
    PawnModel *pawnToValidate;
    if (pawn) {
        pawnToValidate = pawn;
    } else {
        pawnToValidate = activePawn;
    }

    switch (pawnToValidate->type) {
    case PawnType::king:
        return validateKingPawnMove(positionToMove, pawnToValidate);
    case PawnType::queen:
        return validateQueenPawnMove(positionToMove, pawnToValidate, requestedActivePawnPosition);
    case PawnType::rook:
        return validateRookPawnMove(positionToMove, pawnToValidate, requestedActivePawnPosition);
    case PawnType::bishop:
        return validateBishopPawnMove(positionToMove, pawnToValidate, requestedActivePawnPosition);
    case PawnType::knight:
        return validateKnightPawnMove(positionToMove, pawnToValidate);
    case PawnType::pawn:
        return validateBasePawnMove(positionToMove, pawnToValidate, requestedActivePawnPosition);
    }
}

bool BoardViewModel::didRemoveEnemyOnBoardPosition(BoardPosition boardPosition) {
    PawnModel *pawn = getPawnOnBoardPosition(boardPosition);

    if (pawn && pawn->owner == whosTurn) {
        return false;
    }

    if (pawn) {
        switch (whosTurn) {
        case PlayerType::black: {
            int index = whitePawns.indexOf(pawn);
            whitePawns.removeAt(index);
        }
            break;
        case PlayerType::white: {
            int index = blackPawns.indexOf(pawn);
            blackPawns.removeAt(index);
        }
            break;
        }

        if (pawn->type == PawnType::king) {
            winner = &whosTurn;
        }

        delete pawn;

        return true;
    }

    return false;
}

bool BoardViewModel::isKingInCheck(PlayerType owner,
                                   bool isCheckingActivePlayer,
                                   BoardPosition positionToMoveActivePlayer) {
    PawnModel *king = nullptr;

    if (isCheckingActivePlayer && activePawn->type == PawnType::king) {
        king = activePawn;
    } else {
        switch (owner) {
        case PlayerType::black:
            for (int i = 0; i < blackPawns.length(); i++) {
                PawnModel *pawn = blackPawns[i];
                if (pawn->type == PawnType::king) {
                    king = pawn;
                }
            }
            break;
        case PlayerType::white:
            for (int i = 0; i < whitePawns.length(); i++) {
                PawnModel *pawn = whitePawns[i];
                if (pawn->type == PawnType::king) {
                    king = pawn;
                }
            }
            break;
        }
    }

    if (king) {
        bool isInCheck = false;

        switch (owner) {
        case PlayerType::black:
            isInCheck = validateKingsCheckForPawns(whitePawns, isCheckingActivePlayer, king, positionToMoveActivePlayer);
            break;
        case PlayerType::white:
            isInCheck = validateKingsCheckForPawns(blackPawns, isCheckingActivePlayer, king, positionToMoveActivePlayer);
        }

        return isInCheck;
    }

    return false;
}

bool BoardViewModel::didPromoteActivePawn() {
    if (!activePawn) {
        return false;
    }

    if (activePawn->type != PawnType::pawn) {
        return false;
    }

    switch (activePawn->owner) {
    case PlayerType::black:
        if (activePawn->position.y == 7) {
            activePawn->type = PawnType::queen;
            return true;
        }
        break;
    case PlayerType::white:
        if (activePawn->position.y == 0) {
            activePawn->type = PawnType::queen;
            return true;
        }
        break;
    }

    return false;
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

/*
    Castling consists of moving the king two squares towards a rook on the player's first rank,
    Castling may only be done if the king has never moved, the rook involved has never moved,
    the squares between the king and the rook involved are unoccupied, the king is not in check,
    and the king does not cross over or end on a square attacked by an enemy piece.
    Castling is one of the rules of chess and is technically a king move
*/
bool BoardViewModel::isCastlingAvailable() {
    return false;
}

/*
    Promotion in chess is a rule that requires a pawn that reaches its eighth rank to be immediately
    replaced by the player's choice of a queen, knight, rook, or bishop of the same color.
    The new piece replaces the pawn, as part of the same move.
    The choice of new piece is not limited to pieces previously captured, thus promotion can result in a player owning,
    for example, two or more queens despite starting the game with one.
 */
bool BoardViewModel::isPawnPromotionAvailable() {
    return false;
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

bool BoardViewModel::validateKingPawnMove(BoardPosition positionToMove, PawnModel *pawnToValidate) {
    PawnModel *pawn = getPawnOnBoardPosition(positionToMove);

    if (pawn && pawn->owner == pawnToValidate->owner) {
        return false;
    }

    return pawnWantsToMoveByOneField(positionToMove, pawnToValidate);
}

bool BoardViewModel::validateQueenPawnMove(BoardPosition positionToMove, PawnModel *pawnToValidate, BoardPosition *requestedActivePawnPosition) {
    PawnModel *pawn = getPawnOnBoardPosition(positionToMove);

    if (pawn && pawn->owner == pawnToValidate->owner) {
        return false;
    }

    if (validateRookPawnMove(positionToMove, pawnToValidate, requestedActivePawnPosition)) {
        return true;
    }

    return validateBishopPawnMove(positionToMove, pawnToValidate, requestedActivePawnPosition);
}

bool BoardViewModel::validateRookPawnMove(BoardPosition positionToMove, PawnModel *pawnToValidate, BoardPosition *requestedActivePawnPosition) {
    PawnModel *pawn = getPawnOnBoardPosition(positionToMove);

    if (pawn && pawn->owner == pawnToValidate->owner) {
        return false;
    }

    if ((positionToMove.x != pawnToValidate->position.x && positionToMove.y != pawnToValidate->position.y)) {
        return false;
    }

    return validateAnotherPawnIntersection(positionToMove, pawnToValidate, requestedActivePawnPosition);
}

bool BoardViewModel::validateBishopPawnMove(BoardPosition positionToMove, PawnModel *pawnToValidate, BoardPosition *requestedActivePawnPosition) {
    PawnModel *pawn = getPawnOnBoardPosition(positionToMove);

    if (pawn && pawn->owner == pawnToValidate->owner) {
        return false;
    }

    int xDiference = positionToMove.x - pawnToValidate->position.x;
    int yDiference = positionToMove.y - pawnToValidate->position.y;

    if (abs(xDiference) != abs(yDiference)) {
        return false;
    }

    return validateAnotherPawnIntersection(positionToMove, pawnToValidate, requestedActivePawnPosition);
}

bool BoardViewModel::validateKnightPawnMove(BoardPosition positionToMove, PawnModel *pawnToValidate) {
    PawnModel *pawn = getPawnOnBoardPosition(positionToMove);

    if (pawn && pawn->owner == pawnToValidate->owner) {
        return false;
    }

    int xDiference = abs(positionToMove.x - pawnToValidate->position.x);
    int yDiference = abs(positionToMove.y - pawnToValidate->position.y);

    if (xDiference == 2 && yDiference == 1) {
        return true;
    }

    if (xDiference == 1 && yDiference == 2) {
        return true;
    }

    return false;
}

/*
    Pawns cannot move backwards.
    Normally a pawn moves by advancing a single square, but the first time a pawn moves, it has the option of advancing two squares
    Pawns may not use the initial two-square advance to jump over an occupied square, or to capture
    Any piece immediately in front of a pawn, friend or foe, blocks its advance

    En passant capture. It can occur after a pawn advances two squares using its initial two-step move option,
    and the square passed over is attacked by an enemy pawn.
    The enemy pawn is entitled to capture the moved pawn "in passing" – as if it had advanced only one square.
    The capturing pawn moves to the square over which the moved pawn passed, and the moved pawn is removed from the board.
    The option to capture the moved pawn en passant must be exercised on the move immediately following the double-step pawn advance,
    or it is lost for the remainder of the game.
*/

bool BoardViewModel::validateBasePawnMove(BoardPosition positionToMove,
                                          PawnModel *pawnToValidate,
                                          BoardPosition *requestedActivePawnPosition) {
    PawnModel *pawn = getPawnOnBoardPosition(positionToMove);

    if (pawn && pawn->owner == pawnToValidate->owner) {
        return false;
    }

    int xDiference = positionToMove.x - pawnToValidate->position.x;
    int yDiference = positionToMove.y - pawnToValidate->position.y;
    int numbeOfFieldsToMove = std::max(abs(xDiference), abs(yDiference));

    bool wantsToMoveByOneField = (numbeOfFieldsToMove == 1);

    if (abs(xDiference) > 1 || abs(yDiference) > 2) {
        return false;
    }

    if ( !wantsToMoveByOneField && pawnToValidate->didTakeFirstMove) {
        return false;
    }

    bool wantsToMoveInGoodDirection;

    switch (pawnToValidate->owner) {
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
            return (wantsToMoveInGoodDirection && !pawn);
        } else if (requestedActivePawnPosition) {
            return (wantsToMoveInGoodDirection &&
                    requestedActivePawnPosition->x == positionToMove.x &&
                    requestedActivePawnPosition->y == positionToMove.y) || (wantsToMoveInGoodDirection && pawn);
        } else {
            return (wantsToMoveInGoodDirection && pawn);
        }
    }

    return (wantsToMoveInGoodDirection && !pawnToValidate->didTakeFirstMove && xDiference == 0);
}

bool BoardViewModel::validateAnotherPawnIntersection(BoardPosition positionToMove,
                                                     PawnModel *pawnToValidate,
                                                     BoardPosition *requestedActivePawnPosition) {
    int xDiference = positionToMove.x - pawnToValidate->position.x;
    int yDiference = positionToMove.y - pawnToValidate->position.y;
    int numbeOfFieldsToCheck = std::max(abs(xDiference), abs(yDiference));

    if (numbeOfFieldsToCheck == 1) {
        return true;
    }

    for (int i = 0; i < numbeOfFieldsToCheck; i++) {
        BoardPosition positionToCheck;

        if (xDiference < 0) {
            if (yDiference == 0) {
                positionToCheck = { pawnToValidate->position.x + (xDiference + i), pawnToValidate->position.y };
            } else if (yDiference < 0) {
                positionToCheck = { pawnToValidate->position.x + (xDiference + i), pawnToValidate->position.y + (yDiference + i) };
            } else {
                positionToCheck = { pawnToValidate->position.x + (xDiference + i), pawnToValidate->position.y + (yDiference - i) };
            }
        } else if (yDiference < 0) {
            if (xDiference == 0) {
                positionToCheck = { pawnToValidate->position.x, pawnToValidate->position.y + (yDiference + i) };
            } else {
                positionToCheck = { pawnToValidate->position.x + (xDiference - i), pawnToValidate->position.y + (yDiference + i) };
            }
        } else {
            if (xDiference == 0) {
                positionToCheck = { pawnToValidate->position.x, pawnToValidate->position.y + (yDiference - i) };
            } else if (yDiference == 0) {
                positionToCheck = { pawnToValidate->position.x + (xDiference - i), pawnToValidate->position.y };
            } else {
                positionToCheck = { pawnToValidate->position.x + (xDiference - i), pawnToValidate->position.y + (yDiference - i) };
            }
        }

        PawnModel *pawnToCheck = getPawnOnBoardPosition(positionToCheck);

        if (requestedActivePawnPosition &&
                positionToCheck.x != positionToMove.x &&
                positionToCheck.y != positionToMove.y &&
                positionToCheck.x == requestedActivePawnPosition->x &&
                positionToCheck.y == requestedActivePawnPosition->y) {
            return false;
        }

        // if we check for pawn that is on the position that the pawn wants to move by we need to check
        // if this position is not position that the pawm wants to move to
        if (pawnToCheck &&
                (pawnToCheck->position.x != positionToMove.x || pawnToCheck->position.y != positionToMove.y)) {
            return false;
        }
    }

    return true;
}

bool BoardViewModel::pawnWantsToMoveByOneField(BoardPosition positionToMove, PawnModel *pawnToValidate) {
    int xDiference = positionToMove.x - pawnToValidate->position.x;
    int yDiference = positionToMove.y - pawnToValidate->position.y;
    int numbeOfFieldsToMove = std::max(abs(xDiference), abs(yDiference));

    return (numbeOfFieldsToMove == 1);
}

bool BoardViewModel::validateKingsCheckForPawns(QList<PawnModel*> pawns,
                                                bool isCheckingActivePlayer,
                                                PawnModel *king,
                                                BoardPosition positionToMoveActivePlayer) {
    bool isInCheck = false;

    // chech every oppisite players pawn for kings check
    for (int i = 0; i < pawns.length(); i++) {
        PawnModel *pawn = pawns[i];
        // when checking for active player check we need to check first if the active player pawn is king,
        // if it's a king then check if position that wants to move the king to
        // is able to be taken in the next move by the opposite player
        if (isCheckingActivePlayer && activePawn->type == PawnType::king) {
            if (validatePawnMove(positionToMoveActivePlayer, pawn, &positionToMoveActivePlayer)) {
                isInCheck = true;
            }
        } else if (isCheckingActivePlayer) {
            // if the active player pawn is not a king then check if active player wants to move to
            // the place of opposite player pawn that could capture active player king in the next move.
            // If he wants to move to other field then check if the field he wants to take will take active
            // player king from the check state

            if ((positionToMoveActivePlayer.x != pawn->position.x || positionToMoveActivePlayer.y != pawn->position.y) &&
                    validatePawnMove(king->position, pawn, &positionToMoveActivePlayer)) {
                isInCheck = true;
            }

        } else if (validatePawnMove(king->position, pawn)) {
            isInCheck = true;
        }
    }

    return isInCheck;
}
