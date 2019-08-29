#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "boardview.h"
#include "boardviewmodel.h"
#include "pawn.h"

class GameView : public QGraphicsView {
    Q_OBJECT

public:
    GameView();

    QGraphicsScene *scene;
    PlayerType whosTurn;
    BoardView *board;
    Pawn *activePawn;

    void displayMainMenu();

public slots:
    void startGame();
    void quitGame();

private:
    bool gameStarted;
    BoardViewModel boardViewModel;

    void drawBoard();
    void drawSettingsPanel();
    void drawUserPanel();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void selectPawn(Pawn *pawn);
    void placePawnOnField(BoardField *field);
    void moveActivePawnToSelectedPoint(QPoint point);
    void releaseActivePawn();
};

#endif // GAME_H
