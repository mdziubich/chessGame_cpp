#include "pawnfield.h"
#include "boardfield.h"
#include "boardposition.h"
#include "gameview.h"
#include <QLabel>
#include <QGraphicsProxyWidget>

extern GameView *game;

PawnField::PawnField(BoardPosition position,
                     QString imagePath,
                     QGraphicsItem *parent): QGraphicsRectItem(parent) {
    this->position = position;

    setPen(Qt::NoPen);
    setInitialImage(imagePath);
}

void PawnField::setPosition(BoardPosition position) {
    this->position = position;
}

BoardPosition PawnField::getPosition() {
    return position;
}

void PawnField::setInitialImage(QString imagePath) {
    QPixmap image(imagePath);
    QLabel *imageLabel = new QLabel();
    QGraphicsProxyWidget *pMyProxy = new QGraphicsProxyWidget(this);

    imageLabel->setPixmap(image);
    imageLabel->setAttribute(Qt::WA_TranslucentBackground);
    pMyProxy->setWidget(imageLabel);
}
