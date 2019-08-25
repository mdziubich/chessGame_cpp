#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <boardview.h>

class Game : public QGraphicsView {
    Q_OBJECT
public:
    Game(QWidget *parent = NULL);

    QGraphicsScene *scene;
    QString whosTurnLabel;
    BoardView *board;

    void displayMainMenu();

public slots:
    void startGame();
    void quitGame();
};

#endif // GAME_H
