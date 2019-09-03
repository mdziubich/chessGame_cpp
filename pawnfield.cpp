#include "pawnfield.h"
#include <QGraphicsProxyWidget>
#include "boardfield.h"
#include "boardposition.h"
#include "gameview.h"
#include "utils.h"

extern GameView *game;

PawnField::PawnField(BoardPosition position,
                     QString imagePath,
                     QGraphicsItem *parent): QGraphicsRectItem(parent) {
    this->position = position;
    imageLabel = new QLabel();
    image = QPixmap(imagePath);
    QGraphicsProxyWidget *pMyProxy = new QGraphicsProxyWidget(this);

    imageLabel->setPixmap(image);
    imageLabel->setAttribute(Qt::WA_TranslucentBackground);
    pMyProxy->setWidget(imageLabel);

    setPen(Qt::NoPen);
}

void PawnField::setPosition(BoardPosition position) {
    this->position = position;
}

void PawnField::setImage(QString imagePath) {
    image.load(imagePath);
    imageLabel->clear();
    imageLabel->setPixmap(image);
}

BoardPosition PawnField::getPosition() {
    return position;
}
