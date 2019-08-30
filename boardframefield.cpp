#include "boardframefield.h"
#include "utils.h"
#include "gameview.h"
#include <QFont>

extern GameView *game;

BoardFrameField::BoardFrameField(QGraphicsItem *parent): QGraphicsRectItem(parent) {
    QColor backgroundColor = QColor(55, 51, 63);
    Utils::setBackgroundColor(backgroundColor, this);
    setPen(Qt::NoPen);
}

void BoardFrameField::setTitle(QString title) {
    QGraphicsTextItem *titleItem = new QGraphicsTextItem(title);
    QColor textColor = QColor(157, 128, 101);
    QFont titleFont("avenir", 16);
    titleItem->setDefaultTextColor(textColor);
    titleItem->setFont(titleFont);

    double titleXPosition = this->pos().x() + this->boundingRect().width()/2 - titleItem->boundingRect().width()/2;
    double titleYPosition = this->pos().y() + this->boundingRect().height()/2 - titleItem->boundingRect().height()/2;;
    titleItem->setPos(titleXPosition, titleYPosition);
    game->scene->addItem(titleItem);
}
