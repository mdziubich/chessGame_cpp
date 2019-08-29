#include "gameview.h"
#include "boardview.h"
#include "actionbutton.h"
#include <QGraphicsTextItem>
#include <utils.h>

GameView::GameView() {

    boardViewModel = BoardViewModel();

    int viewWidth = 1024;
    int viewHeight= 768;

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(viewWidth, viewHeight);

    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, viewWidth, viewHeight);
    setScene(scene);

    whosTurn = PlayerType::playerOne;
    activePawn = nullptr;
    gameStarted = false;
}


void GameView::displayMainMenu() {
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

    connect(startButton, SIGNAL(buttonPressed()), this, SLOT(startGame()));
    scene->addItem(startButton);

    // create quit button
    ActionButton *quitButton = new ActionButton(QString("Quit"));
    double quitXPosition = this->width()/2 - quitButton->boundingRect().width()/2;
    double quitYPosition = 350;
    quitButton->setPos(quitXPosition, quitYPosition);

    connect(quitButton, SIGNAL(buttonPressed()), this, SLOT(quitGame()));
    scene->addItem(quitButton);
}

void GameView::startGame() {
    // clear the screen
    scene->clear();

    drawBoard();
    drawSettingsPanel();
    drawUserPanel();
    gameStarted = true;
}

void GameView::quitGame() {
    gameStarted = false;
}

void GameView::drawBoard() {
    board = new BoardView();
    board->draw();
}

void GameView::drawSettingsPanel() {
    QGraphicsTextItem *settingsTitle = new QGraphicsTextItem("Settings");
    settingsTitle->setPos(600, 100);
    scene->addItem(settingsTitle);

    QGraphicsRectItem *settingsPanel = new QGraphicsRectItem(600, 100, 300, 480);
    Utils::setBackgroundColor(Qt::blue, settingsPanel);
    settingsPanel->setOpacity(0.5);
    scene->addItem(settingsPanel);
}

void GameView::drawUserPanel() {

}

void GameView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        releaseActivePawn();
    } else if (activePawn) {
        moveActivePawnToSelectedPoint(event->pos());
    } else if (gameStarted) {
        // select pawn
        Pawn *pawn = board->getPawnAtMousePosition(event->pos());
        selectPawn(pawn);
    }

    QGraphicsView::mousePressEvent(event);
}

void GameView::moveActivePawnToSelectedPoint(QPoint point) {
    if (boardViewModel.validatePawnPalcementForMousePosition(point)) {
        BoardPosition boardPosition = boardViewModel.getBoardPositionForMousePosition(point);
        board->placePawnAtBoardPosition(activePawn, boardPosition);
        activePawn = nullptr;
    }
}

void GameView::mouseMoveEvent(QMouseEvent *event) {
    // if there is a pawn selected, then make it follow the mouse
    if (activePawn) {
        board->moveActivePawnToMousePosition(event->pos(), activePawn);
    }

    QGraphicsView::mouseMoveEvent(event);
}


void GameView::selectPawn(Pawn *pawn) {
    if (pawn == nullptr) {
        return;
    }

    if (pawn->owner == whosTurn) {
        activePawn = pawn;
        // move selected pawn to the front
        activePawn->setZValue(1);
    }
}

void GameView::placePawnOnField(BoardField *field) {
    if (activePawn == nullptr) {
        return;
    }
    // if this filed is NOT placed then validate move and place pawn if possible

    // if this field is placed then validate move and remove opposite pawn if possible

    activePawn->setPos(field->pos());
    activePawn->setPosition(field->getPosition());
    activePawn->setZValue(0);

    // first validate Move

    // check if field was taken by opposite player

    // remove opposite player pawn

    // check for king's check

    // check is game is over

    // clear active pawn
    activePawn = nullptr;

    // change round owner to opposite player
}

void GameView::releaseActivePawn() {
    if (activePawn == nullptr) {
        return;
    }

    QPointF coordinates = boardViewModel.getCoordinatesForBoardPosition(activePawn->getPosition());
    activePawn->setPos(coordinates);
    activePawn->setZValue(0);

    activePawn = nullptr;
}
