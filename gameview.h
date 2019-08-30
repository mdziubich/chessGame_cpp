#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "boardview.h"
#include "boardviewmodel.h"
#include "pawnfield.h"
#include "playerview.h"

class GameView : public QGraphicsView {
    Q_OBJECT

public:
    GameView();

    QGraphicsScene *scene;

    void displayMainMenu();

public slots:
    void startGame();
    void quitGame();

private:
    BoardViewModel boardViewModel;
    bool gameStarted;
    BoardView *board;
    PlayerView *blackPlayerView;
    PlayerView *whitePlayerView;

    void drawBoard();
    void drawSettingsPanel();
    void drawUserPanel();
    PlayerView* drawViewForUser(PlayerType player);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void selectPawn(PawnField *pawn);
    void handleSelectingPointForActivePawnByMouse(QPoint point);
    void moveActivePawnToSelectedPoint(QPoint point);
    void releaseActivePawn();
};

#endif // GAME_H
