#include "pawn.h"
#include "boardfield.h"
#include "boardposition.h"
#include "gameview.h"
#include <QLabel>
#include <QGraphicsProxyWidget>

extern GameView *game;

Pawn::Pawn(BoardPosition position, QGraphicsItem *parent): QGraphicsRectItem(parent) {
    this->position = position;
    owner = getPlayerForInitialPosition(position);

    setPen(Qt::NoPen);
    setInitialImage();
}

void Pawn::setPosition(BoardPosition position) {
    this->position = position;
}

BoardPosition Pawn::getPosition() {
    return position;
}

void Pawn::setInitialImage() {
    PawnType type = getTypeForInitialPosition(position);
    PlayerType player = getPlayerForInitialPosition(position);
    QString imageFilePath = getImagePath(type, player);
    QPixmap image(imageFilePath);
    QLabel *imageLabel = new QLabel();
    QGraphicsProxyWidget *pMyProxy = new QGraphicsProxyWidget(this);

    imageLabel->setPixmap(image);
    imageLabel->setAttribute(Qt::WA_TranslucentBackground);
    pMyProxy->setWidget(imageLabel);
}

QString Pawn::getImagePath(PawnType type, PlayerType player) {
    QString imageFileName;

    switch (type) {
    case PawnType::king:
        if (player == PlayerType::playerOne) {
            imageFileName = "king_black.svg";
        } else {
            imageFileName = "king_white.svg";
        }
        break;
    case PawnType::queen:
        if (player == PlayerType::playerOne) {
            imageFileName = "queen_black.svg";
        } else {
            imageFileName = "queen_white.svg";
        }
        break;
    case PawnType::rook:
        if (player == PlayerType::playerOne) {
            imageFileName = "rook_black.svg";
        } else {
            imageFileName = "rook_white.svg";
        }
        break;
    case PawnType::bishop:
        if (player == PlayerType::playerOne) {
            imageFileName = "bishop_black.svg";
        } else {
            imageFileName = "bishop_white.svg";
        }
        break;
    case PawnType::knight:
        if (player == PlayerType::playerOne) {
            imageFileName = "knight_black.svg";
        } else {
            imageFileName = "knight_white.svg";
        }
        break;
    case PawnType::pawn:
        if (player == PlayerType::playerOne) {
            imageFileName = "pawn_black.svg";
        } else {
            imageFileName = "pawn_white.svg";
        }
        break;
    }

    return ":Images/" + imageFileName;
}

PawnType Pawn::getTypeForInitialPosition(BoardPosition position) {
    if (position.y == 1 || position.y == 6) {
        return PawnType::pawn;
    }

    switch (position.x) {
    case 0:
    case 7:
        return PawnType::rook;
    case 1:
    case 6:
        return PawnType::knight;
    case 2:
    case 5:
        return PawnType::bishop;
    case 3:
        return PawnType::queen;
    case 4:
        return PawnType::king;
    }

    return PawnType::pawn;
}

PlayerType Pawn::getPlayerForInitialPosition(BoardPosition position) {
    if (position.y == 0 || position.y == 1) {
        return PlayerType::playerOne;
    }
    return PlayerType::playerTwo;
}
