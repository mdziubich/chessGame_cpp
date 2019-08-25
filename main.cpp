#include <QApplication>
#include <ChessGame.h>

ChessGame *game;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    game = new ChessGame();
    game->show();
    game->start();

    return a.exec();
}
