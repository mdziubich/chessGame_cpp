#include "boardview.h"
#include <boardfield.h>
#include <gameview.h>
#include <boardposition.h>
#include <pawn.h>

extern GameView *game;

int BoardView::numberOfRowsColumns = 8;
int BoardView::startXPosition = 100;
int BoardView::startYPosition = 100;

BoardView::BoardView() {
    int size = numberOfRowsColumns * BoardField::defaultWidthHeight;
    setRect(startXPosition, startYPosition, size, size);
    game->scene->addItem(this);
}

void BoardView::draw() {
    placeBoardFields();
    placePawns();
}

QList<BoardField*> BoardView::getFields() {
    return fields;
}

void BoardView::placePawnAtBoardPosition(Pawn *pawn, BoardPosition boardPosition) {
    int newXPosition = startXPosition + boardPosition.x * BoardField::defaultWidthHeight;
    int newYPosition = startYPosition + boardPosition.y * BoardField::defaultWidthHeight;

    pawn->setPos(newXPosition, newYPosition);
    pawn->setPosition(boardPosition);
}

void BoardView::moveActivePawnToMousePosition(QPoint point, Pawn *pawn) {
    int xPosition = point.x() - BoardField::defaultWidthHeight/2;
    int yPosition = point.y() - BoardField::defaultWidthHeight/2;

    pawn->setPos(xPosition, yPosition);
}

Pawn* BoardView::getPawnAtMousePosition(QPoint point) {
    for (int i = 0; i < pawns.length(); i++) {
        Pawn *pawn = pawns[i];
        QPointF pawnPos = pawn->pos();

        if ((point.x() < (pawnPos.x() + pawn->rect().width())) &&
                (point.x() > pawnPos.x()) &&
                (point.y() < (pawnPos.y() + pawn->rect().height())) &&
                (point.y() > pawnPos.y())) {
            return pawn;
        }
    }

    return nullptr;
}

Pawn* BoardView::getPawnAtBoardPosition(BoardPosition boardPosition) {
    for (int i = 0; i < pawns.length(); i++) {
        BoardPosition pawnPosition = pawns[i]->getPosition();

        if (pawnPosition.x == boardPosition.x && pawnPosition.y == boardPosition.y) {
            return pawns[i];
        }
    }

    return nullptr;
}

void BoardView::placeBoardFields() {
    for (int i = 0; i< numberOfRowsColumns; i++ ) {
        int xPosition = i * BoardField::defaultWidthHeight;
        createFieldsColumn(xPosition, i);
    }
}

// creates a column of fields at the specified location with specified number of rows
void BoardView::createFieldsColumn(int xPosition, int columnNumber) {
    for (int rowNumber = 0; rowNumber < numberOfRowsColumns; rowNumber++) {
        Qt::GlobalColor backgroundColor;
        if (columnNumber % 2 == 0) {
            if (rowNumber % 2 == 0) {
                backgroundColor = Qt::white;
            } else {
                backgroundColor = Qt::black;
            }
        } else {
            if (rowNumber % 2 == 0) {
                backgroundColor = Qt::black;
            } else {
                backgroundColor = Qt::white;
            }
        }

        BoardPosition position = { columnNumber, rowNumber };
        BoardField *field = new BoardField(backgroundColor, position, this);
        int filedYPosition = startYPosition + rowNumber * BoardField::defaultWidthHeight;
        field->setRect(xPosition + startXPosition,
                       filedYPosition,
                       BoardField::defaultWidthHeight,
                       BoardField::defaultWidthHeight);
        fields.append(field);
    }
}

void BoardView::placePawns() {
    placePawnsForRow(0);
    placePawnsForRow(1);
    placePawnsForRow(6);
    placePawnsForRow(7);
}

void BoardView::placePawnsForRow(int rowNumber) {
    for (int i = 0; i < numberOfRowsColumns; i++) {
        BoardPosition boardPosition = { i, rowNumber };
        Pawn *pawn = pawn = new Pawn(boardPosition, this);

        int pawnXPosition = startXPosition + i * BoardField::defaultWidthHeight;
        int pawnYPosition = startYPosition + rowNumber * BoardField::defaultWidthHeight;

        pawn->setRect(0, 0, BoardField::defaultWidthHeight, BoardField::defaultWidthHeight);
        pawn->setPos(pawnXPosition, pawnYPosition);

        pawns.append(pawn);
    }
}
