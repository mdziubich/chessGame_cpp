#ifndef BOARDVIEWMODEL_H
#define BOARDVIEWMODEL_H

#include <QPoint>
#include "boardposition.h"
#include "pawnfield.h"
#include "pawnmodel.h"
#include "pawnviewModel.h"

class BoardViewModel {

public:
    BoardViewModel();

    bool isEnPassantAvailable;

    QList<PawnModel*> getBlackPawns();
    QList<PawnModel*> getWhitePawns();
    PawnModel* getActivePawn();
    void setActivePawnForField(PawnField *pawn);
    void setNewPositionForActivePawn(BoardPosition position);
    void discardActivePawn();

    BoardPosition getBoardPositionForMousePosition(QPoint position);
    bool validatePawnPalcementForMousePosition(QPoint position);
    bool validatePawnMove(BoardPosition positionToMove);
    void switchRound();
    bool isCastlingAvailable();

    bool shouldReplaceActivePawnWithQueen();

private:
    PawnModel *activePawn;
    PlayerType whosTurn;
    QList<PawnModel*> blackPawns;
    QList<PawnModel*> whitePawns;
    PawnViewModel pawnViewModel;

    void initializePawns();
    void initializePawnsForRow(int rowNumber, PlayerType owner);
    PawnModel* getPawnOnBoardPosition(BoardPosition baordPosition);

    bool validateKingPawnMove(BoardPosition positionToMove);
    bool validateQueenPawnMove(BoardPosition positionToMove);
    bool validateRookPawnMove(BoardPosition positionToMove);
    bool validateBishopPawnMove(BoardPosition positionToMove);
    bool validateKnightPawnMove(BoardPosition positionToMove);
    bool validateBasePawnMove(BoardPosition positionToMove);
    bool validateAnotherPawnIntersection(BoardPosition positionToMove);
    bool isFieldOccupiedByEnemy(BoardPosition fieldPosition);
};

#endif // BOARDVIEWMODEL_H
