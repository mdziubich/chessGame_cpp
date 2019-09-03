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
    PlayerType getWhosTurn();
    PlayerType* getWinner();
    void setActivePawnForField(PawnField *pawn);
    void setNewPositionForActivePawn(BoardPosition position);
    void discardActivePawn();
    BoardPosition getBoardPositionForMousePosition(QPoint position);
    bool validatePawnPalcementForMousePosition(QPoint position);
    bool validatePawnMove(BoardPosition positionToMove, PawnModel *pawnToValidate = nullptr, BoardPosition *requestedActivePawnPosition = nullptr);
    bool didRemoveEnemyOnBoardPosition(BoardPosition boardPosition);
    bool isKingInCheck(PlayerType owner, bool isCheckingActivePlayer, BoardPosition positionToMoveActivePlayer);
    bool didPromoteActivePawn();
    void switchRound();

    bool isCastlingAvailable();
    bool isPawnPromotionAvailable();
    bool shouldReplaceActivePawnWithQueen();

private:
    PawnModel *activePawn;
    PlayerType whosTurn;
    QList<PawnModel*> blackPawns;
    QList<PawnModel*> whitePawns;
    PawnViewModel pawnViewModel;
    PlayerType *winner;

    void initializePawns();
    void initializePawnsForRow(int rowNumber, PlayerType owner);
    PawnModel* getPawnOnBoardPosition(BoardPosition baordPosition);
    bool validateKingPawnMove(BoardPosition positionToMove, PawnModel *pawnToValidate);
    bool validateQueenPawnMove(BoardPosition positionToMove, PawnModel *pawnToValidate, BoardPosition *requestedActivePawnPosition = nullptr);
    bool validateRookPawnMove(BoardPosition positionToMove, PawnModel *pawnToValidate, BoardPosition *requestedActivePawnPosition = nullptr);
    bool validateBishopPawnMove(BoardPosition positionToMove, PawnModel *pawnToValidate, BoardPosition *requestedActivePawnPosition = nullptr);
    bool validateKnightPawnMove(BoardPosition positionToMove, PawnModel *pawnToValidate);
    bool validateBasePawnMove(BoardPosition positionToMove, PawnModel *pawnToValidate, BoardPosition *requestedActivePawnPosition = nullptr);
    bool validateAnotherPawnIntersection(BoardPosition positionToMove, PawnModel *pawnToValidate, BoardPosition *requestedActivePawnPosition = nullptr);
    bool pawnWantsToMoveByOneField(BoardPosition positionToMove, PawnModel *pawnToValidate);
    bool validateKingsCheckForPawns(QList<PawnModel*> pawns, bool isCheckingActivePlayer, PawnModel *king, BoardPosition positionToMoveActivePlayer);
};

#endif // BOARDVIEWMODEL_H
