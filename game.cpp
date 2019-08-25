#include "game.h"
#include "boardview.h"
#include "actionbutton.h"
#include <QGraphicsTextItem>

Game::Game(QWidget *parent) {

    int viewWidth = 1024;
    int viewHeight= 768;

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(viewWidth, viewHeight);

    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, viewWidth, viewHeight);
    setScene(scene);
}


void Game::displayMainMenu() {
    // create title label
    QGraphicsTextItem *title = new QGraphicsTextItem(QString("Chess Game"));
    QFont titleFont("avenir", 50);
    title->setFont(titleFont);
    double titleXPosition = this->width()/2 - title->boundingRect().width()/2;
    double titleYPosition = 150;
    title->setPos(titleXPosition, titleYPosition);
    scene->addItem(title);

    // create start button
    ActionButton *startButton = new ActionButton(QString("Play"));
    double buttonXPosition = this->width()/2 - startButton->boundingRect().width()/2;
    double buttonYPosition = 275;
    startButton->setPos(buttonXPosition, buttonYPosition);

    connect(startButton, SIGNAL(clicked()), this, SLOT(startGame()));
    scene->addItem(startButton);

    // create quit button
    ActionButton *quitButton = new ActionButton(QString("Quit"));
    double quitXPosition = this->width()/2 - quitButton->boundingRect().width()/2;
    double quitYPosition = 350;
    quitButton->setPos(quitXPosition, quitYPosition);

    connect(quitButton, SIGNAL(clicked()), this, SLOT(quitGame()));
    scene->addItem(quitButton);
}

void Game::startGame() {
    // clear the screen
    scene->clear();

    drawBoard();
    drawSettingsPanel();
    drawUserPanel();
}

void Game::quitGame() {

}

void Game::drawBoard() {
    board = new BoardView();
    board->draw();
}

void Game::drawSettingsPanel() {
    QGraphicsTextItem *settingsTitle = new QGraphicsTextItem("Settings");
    settingsTitle->setPos(600, 100);
    scene->addItem(settingsTitle);

    QGraphicsRectItem *settingsPanel = new QGraphicsRectItem(600, 100, 300, 480);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::blue);
    settingsPanel->setBrush(brush);
    settingsPanel->setOpacity(0.5);
    scene->addItem(settingsPanel);
}

void Game::drawUserPanel() {

}
