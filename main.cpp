#include <QApplication>
#include <gameview.h>

GameView *game;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    game = new GameView();
    game->show();
    game->displayMainMenu();

    return a.exec();
}
