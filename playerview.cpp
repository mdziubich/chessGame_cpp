#include "playerview.h"
#include <QObject>
#include <QFont>
#include "constants.h"
#include "gameview.h"
#include "utils.h"

int PlayerView::defaultWidthHeight = 200;
extern GameView *game;

PlayerView::PlayerView(QGraphicsItem *parent): QGraphicsRectItem(parent) {
    QColor backgroundColor = QColor(55, 51, 63);
    Utils::setBackgroundColor(backgroundColor, this);
    setPen(Qt::NoPen);
}

void PlayerView::setPlayer(PlayerType owner) {
    QString title;
    QString imagePath;

    switch (owner) {
    case PlayerType::black:
        title = "Black Player";
        imagePath = ":Images/pawn_black.svg";
        break;
    case PlayerType::white:
        title = "White Player";
        imagePath = ":Images/pawn_white.svg";
        break;
    }

    // set title
    QGraphicsTextItem *titleItem = new QGraphicsTextItem(title, this);
    QColor textColor = QColor(157, 128, 101);
    QFont titleFont("avenir", 18);
    titleItem->setDefaultTextColor(textColor);
    titleItem->setFont(titleFont);

    double titleXPosition = this->boundingRect().x() + this->boundingRect().width()/2 - titleItem->boundingRect().width()/2;
    double titleYPosition = this->boundingRect().y() + defaultWidthHeight - titleItem->boundingRect().height()/2 - Constants::defaultMargin;
    titleItem->setPos(titleXPosition, titleYPosition);

    // set image
    PawnField *pawn = new PawnField({ 0, 0 }, imagePath, this);

    double pawnXPosition = this->boundingRect().x() + this->boundingRect().width()/2 - BoardField::defaultWidthHeight/2;
    double pawnYPosition = this->boundingRect().y() + Constants::defaultMargin;

    pawn->setRect(0, 0, BoardField::defaultWidthHeight, BoardField::defaultWidthHeight);
    pawn->setPos(pawnXPosition, pawnYPosition);

}

void PlayerView::setActive(bool active) {
    QColor borderColor;

    if (active) {
        borderColor = QColor(157, 128, 101);
    } else {
        borderColor = QColor(55, 51, 63);
    }

    QPen pen(borderColor);
    setPen(pen);
}
