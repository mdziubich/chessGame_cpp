#include "gameview.h"
#include <QGraphicsTextItem>
#include <QColor>
#include <QBrush>
#include "actionbutton.h"
#include "utils.h"

GameView::GameView() {

    boardViewModel = BoardViewModel();

    int viewWidth = 1200;
    int viewHeight= 768;

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(viewWidth, viewHeight);

    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, viewWidth, viewHeight);
    setScene(scene);

    QBrush brush;
    brush.setStyle((Qt::SolidPattern));
    QColor color = QColor(44, 41, 51);
    brush.setColor(color);
    scene->setBackgroundBrush(brush);

    gameStarted = false;
}


void GameView::displayMainMenu() {
    // create title label
    QGraphicsTextItem *title = new QGraphicsTextItem(QString("Chess Game"));
    QColor color = QColor(255, 255, 255);
    QFont titleFont("avenir", 50);
    title->setDefaultTextColor(color);
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
    board->initializePawnFields(boardViewModel.getBlackPawns());
    board->initializePawnFields(boardViewModel.getWhitePawns());
}

void GameView::drawSettingsPanel() {
//    QGraphicsTextItem *settingsTitle = new QGraphicsTextItem("Settings");
//    settingsTitle->setPos(700, 100);
//    scene->addItem(settingsTitle);

//    QGraphicsRectItem *settingsPanel = new QGraphicsRectItem(700, 100, 300, 480);
//    Utils::setBackgroundColor(Qt::blue, settingsPanel);
//    settingsPanel->setOpacity(0.5);
//    scene->addItem(settingsPanel);
}

void GameView::drawUserPanel() {
    blackPlayerView = drawViewForUser(PlayerType::black);
    whitePlayerView = drawViewForUser(PlayerType::white);

    blackPlayerView->setActive(true);
}

PlayerView* GameView::drawViewForUser(PlayerType player) {
    PlayerView *playerView = new PlayerView();

    int xPosition = 80;
    int yPosition = 80;

    switch (player) {
    case PlayerType::black:
        xPosition = 680;
        break;
    case PlayerType::white:
        xPosition = 680 + PlayerView::defaultWidthHeight + 20;
        break;
    }

    scene->addItem(playerView);
    playerView->setRect(xPosition, yPosition, PlayerView::defaultWidthHeight, PlayerView::defaultWidthHeight);
    playerView->setPlayer(player);

    return playerView;
}

void GameView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        releaseActivePawn();
    } else if (boardViewModel.getActivePawn()) {
        handleSelectingPointForActivePawnByMouse(event->pos());
    } else if (gameStarted) {
        PawnField *pawn = board->getPawnAtMousePosition(event->pos());
        selectPawn(pawn);
    }

    QGraphicsView::mousePressEvent(event);
}

void GameView::mouseMoveEvent(QMouseEvent *event) {
    // if there is a pawn selected, then make it follow the mouse
    if (boardViewModel.getActivePawn()) {
        board->moveActivePawnToMousePosition(event->pos(), boardViewModel.getActivePawn());
    }

    QGraphicsView::mouseMoveEvent(event);
}


void GameView::selectPawn(PawnField *pawn) {
    if (pawn == nullptr) {
        return;
    }

    boardViewModel.setActivePawnForField(pawn);
}

void GameView::handleSelectingPointForActivePawnByMouse(QPoint point) {
    if (boardViewModel.getActivePawn() == nullptr) {
        return;
    }

    // check if mouse selected place on board
    if (!boardViewModel.validatePawnPalcementForMousePosition(point)) {
        return;
    }

    BoardPosition boardPosition = boardViewModel.getBoardPositionForMousePosition(point);

    // first validate Move
    if (!boardViewModel.validatePawnMove(boardPosition)) {
        return;
    }

    // Players cannot make any move that places their own king in check.

    // check if field was taken by opposite player and remove it from the board
    if (boardViewModel.didRemoveEnemyOnBoardPosition(boardPosition)) {
        board->removePawnAtBoardPosition(boardPosition);
    }

    // check for rook's castling

    // check if pawn can be promoted

    // remove opposite player pawn

    // check for king's check

    // check is game is over

    // move active pawn to new position
    moveActivePawnToSelectedPoint(point);

    // change round owner to opposite player
    boardViewModel.switchRound();
    blackPlayerView->setActive(boardViewModel.getWhosTurn() == PlayerType::black);
    whitePlayerView->setActive(boardViewModel.getWhosTurn() == PlayerType::white);
}

//update pawn field position and pawn model position
void GameView::moveActivePawnToSelectedPoint(QPoint point) {
    BoardPosition boardPosition = boardViewModel.getBoardPositionForMousePosition(point);
    board->placeActivePawnAtBoardPosition(boardViewModel.getActivePawn(), boardPosition);
    boardViewModel.setNewPositionForActivePawn(boardPosition);
    boardViewModel.discardActivePawn();
}

void GameView::releaseActivePawn() {
    if (boardViewModel.getActivePawn() == nullptr) {
        return;
    }

    PawnModel *activePawn = boardViewModel.getActivePawn();
    board->placeActivePawnAtBoardPosition(activePawn, activePawn->position);
    boardViewModel.discardActivePawn();
}
