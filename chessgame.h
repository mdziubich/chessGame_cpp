#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <boardview.h>

class ChessGame : public QGraphicsView {
public:
    ChessGame(QWidget *parent=NULL);

    QGraphicsScene *scene;
    QString whosTurnLabel;
    BoardView *board;

    void start();
};

#endif // CHESSGAME_H
