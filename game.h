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

private:
    void drawBoard();
    void drawSettingsPanel();
    void drawUserPanel();
};

#endif // GAME_H
