#include "chessgame.h"
#include "boardview.h"

ChessGame::ChessGame(QWidget *parent) {

    int viewWidth = 1024;
    int viewHeight= 768;

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(viewWidth, viewHeight);

    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, viewWidth, viewHeight);
    setScene(scene);
}

void ChessGame::start() {
    board = new BoardView();
    board->draw();
}
