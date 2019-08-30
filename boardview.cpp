#include "boardview.h"
#include <boardfield.h>
#include <gameview.h>
#include <boardposition.h>
#include <pawnfield.h>

extern GameView *game;

int BoardView::numberOfRowsColumns = 8;
int BoardView::startXPosition = 100;
int BoardView::startYPosition = 100;

BoardView::BoardView() {
    int size = numberOfRowsColumns * BoardField::defaultWidthHeight;
    setRect(startXPosition, startYPosition, size, size);
    game->scene->addItem(this);
}

QList<BoardField*> BoardView::getFields() {
    return fields;
}

void BoardView::draw() {
    placeBoardFields();
}

void BoardView::initializePawnFields(QList<PawnModel*> pawns) {
    for (int i = 0; i < pawns.length(); i++) {
        PawnModel *pawnModel = pawns[i];
        PawnField *pawn = new PawnField(pawnModel->position, pawnModel->imagePath, this);

        int pawnXPosition = startXPosition + pawnModel->position.x * BoardField::defaultWidthHeight;
        int pawnYPosition = startYPosition + pawnModel->position.y * BoardField::defaultWidthHeight;

        pawn->setRect(0, 0, BoardField::defaultWidthHeight, BoardField::defaultWidthHeight);
        pawn->setPos(pawnXPosition, pawnYPosition);

        this->pawns.append(pawn);
    }
}

void BoardView::moveActivePawnToMousePosition(QPoint point, PawnModel *pawn) {
    int xPosition = point.x() - BoardField::defaultWidthHeight/2;
    int yPosition = point.y() - BoardField::defaultWidthHeight/2;
    PawnField *pawnField = getPawnAtBoardPosition(pawn->position);

    if (pawnField) {
        pawnField->setPos(xPosition, yPosition);
    }
}

void BoardView::placeActivePawnAtBoardPosition(PawnModel *pawn, BoardPosition boardPosition) {
    PawnField *pawnField = getPawnAtBoardPosition(pawn->position);

    if (pawnField) {
        QPointF coordinates = getCoordinatesForBoardPosition(boardPosition);
        pawnField->setZValue(0);
        pawnField->setPos(coordinates);
        pawnField->setPosition(boardPosition);
    }
}

PawnField* BoardView::getPawnAtMousePosition(QPoint point) {
    for (int i = 0; i < pawns.length(); i++) {
        PawnField *pawn = pawns[i];
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

PawnField* BoardView::getPawnAtBoardPosition(BoardPosition boardPosition) {
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

QPointF BoardView::getCoordinatesForBoardPosition(BoardPosition position) {
    int xPosition = startXPosition + position.x*BoardField::defaultWidthHeight;
    int yPosition = startYPosition + position.y*BoardField::defaultWidthHeight;

    return QPointF(xPosition, yPosition);
}
