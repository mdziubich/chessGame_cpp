#ifndef BOARDVIEWMODEL_H
#define BOARDVIEWMODEL_H

#include <QPoint>
#include "boardposition.h"
#include "pawnfield.h"
#include "basepawnmodel.h"
#include "pawnviewmodel.h"

class BoardViewModel {

public:
    BoardViewModel();

    bool isEnPassantAvailable;

    QList<BasePawnModel*> getBlackPawns();
    QList<BasePawnModel*> getWhitePawns();
    BasePawnModel* getActivePawn();
    PlayerType getWhosTurn();
    PlayerType* getWinner();
    void setActivePawnForField(PawnField *pawn);
    void setNewPositionForActivePawn(BoardPosition position);
    void discardActivePawn();
    BoardPosition getBoardPositionForMousePosition(QPoint position);
    bool validatePawnPalcementForMousePosition(QPoint position);
    bool validatePawnMove(BoardPosition positionToMove, BasePawnModel *pawnToValidate = nullptr, BoardPosition *requestedActivePawnPosition = nullptr);
    bool didRemoveEnemyOnBoardPosition(BoardPosition boardPosition);
    bool isKingInCheck(PlayerType owner, bool isCheckingActivePlayer, BoardPosition positionToMoveActivePlayer);
    bool didPromoteActivePawn();
    void switchRound();

private:
    BasePawnModel *activePawn;
    PlayerType whosTurn;
    QList<BasePawnModel*> blackPawns;
    QList<BasePawnModel*> whitePawns;
    PawnViewModel pawnViewModel;
    PlayerType *winner;

    void initializePawns();
    void initializePawnsForRow(int rowNumber, PlayerType owner);
    BasePawnModel* getPawnOnBoardPosition(BoardPosition baordPosition);
    bool validateAnotherPawnIntersection(BoardPosition positionToMove, BasePawnModel *pawnToValidate, BoardPosition *requestedActivePawnPosition = nullptr);
    bool validateKingsCheckForPawns(QList<BasePawnModel*> pawns, bool isCheckingActivePlayer, BasePawnModel *king, BoardPosition positionToMoveActivePlayer);
};

#endif // BOARDVIEWMODEL_H
