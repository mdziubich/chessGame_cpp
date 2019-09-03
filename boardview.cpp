#include "boardview.h"
#include <QLabel>
#include "boardfield.h"
#include "boardposition.h"
#include "constants.h"
#include "boardframefield.h"
#include "gameview.h"
#include "pawnfield.h"
#include "utils.h"

extern GameView *game;

int BoardView::numberOfRowsColumns = 8;
int BoardView::startXPosition = 100;
int BoardView::startYPosition = 150;

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
    drawBoardFrame();
    drawCheckWarningTextItems();
}

void BoardView::initializePawnFields(QList<BasePawnModel*> pawns) {
    for (int i = 0; i < pawns.length(); i++) {
        BasePawnModel *pawnModel = pawns[i];
        PawnField *pawn = new PawnField(pawnModel->position, pawnModel->imagePath, this);

        int pawnXPosition = startXPosition + pawnModel->position.x * BoardField::defaultWidthHeight;
        int pawnYPosition = startYPosition + pawnModel->position.y * BoardField::defaultWidthHeight;

        pawn->setRect(0, 0, BoardField::defaultWidthHeight, BoardField::defaultWidthHeight);
        pawn->setPos(pawnXPosition, pawnYPosition);

        this->pawns.append(pawn);
    }
}

void BoardView::moveActivePawnToMousePosition(QPoint point, BasePawnModel *pawn) {
    int xPosition = point.x() - BoardField::defaultWidthHeight/2;
    int yPosition = point.y() - BoardField::defaultWidthHeight/2;
    PawnField *pawnField = getPawnAtBoardPosition(pawn->position);

    if (pawnField) {
        pawnField->setPos(xPosition, yPosition);
    }
}

void BoardView::placeActivePawnAtBoardPosition(BasePawnModel *pawn, BoardPosition boardPosition) {
    PawnField *pawnField = getPawnAtBoardPosition(pawn->position);

    if (pawnField) {
        QPointF coordinates = getCoordinatesForBoardPosition(boardPosition);
        pawnField->setZValue(0);
        pawnField->setPos(coordinates);
        pawnField->setPosition(boardPosition);
    }
}

void BoardView::removePawnAtBoardPosition(BoardPosition boardPosition) {
    PawnField *pawnField = getPawnAtBoardPosition(boardPosition);

    game->scene->removeItem(pawnField);

    int index = pawns.indexOf(pawnField);
    pawns.removeAt(index);
    delete pawnField;
}

void BoardView::setPawnMoveCheckWarning(bool visible) {
    int opacity = visible ? 1 : 0;
    checkWarningTitleTextItem->setOpacity(opacity);
    checkWarningDescriptionTextItem->setOpacity(opacity);
}

void BoardView::promotePawnAtBoardPosition(BoardPosition boardPosition) {
    PawnField *pawn = getPawnAtBoardPosition(boardPosition);
    QString imageFileName;
    if (pawn->getPosition().y == 7) {
        imageFileName = ":Images/queen_black.svg";
    } else {
        imageFileName = ":Images/queen_white.svg";
    }
    pawn->setImage(imageFileName);
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
        QColor backgroundColor;
        if (columnNumber % 2 == 0) {
            if (rowNumber % 2 == 0) {
                backgroundColor = QColor(196, 178, 140);
            } else {
                backgroundColor = QColor(157, 128, 101);
            }
        } else {
            if (rowNumber % 2 == 0) {
                backgroundColor = QColor(157, 128, 101);
            } else {
                backgroundColor = QColor(196, 178, 140);
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

void BoardView::drawBoardFrame() {
    QString lettersTitles[] = {"A", "B", "C", "D", "E", "F", "G", "H"};
    QString numberTitles[] = {"1", "2", "3", "4", "5", "6", "7", "8"};

    for (int i = 0; i< numberOfRowsColumns; i++ ) {
        int xPosition = startXPosition + i * BoardField::defaultWidthHeight;
        QPoint point = QPoint(xPosition, startYPosition - 30);
        QRectF rect = QRectF(0, 0, BoardField::defaultWidthHeight, 30);
        drawBoardFrameAtPosition(point, rect, lettersTitles[i]);
    }

    for (int i = 0; i< numberOfRowsColumns; i++ ) {
        int xPosition = startXPosition + i * BoardField::defaultWidthHeight;
        int yPosition = startYPosition + numberOfRowsColumns * BoardField::defaultWidthHeight;
        QPoint point = QPoint(xPosition, yPosition);
        QRectF rect = QRectF(0, 0, BoardField::defaultWidthHeight, 30);
        drawBoardFrameAtPosition(point, rect, lettersTitles[i]);
    }

    for (int i = 0; i< numberOfRowsColumns; i++ ) {
        int yPosition = startYPosition + i * BoardField::defaultWidthHeight;
        QPoint point = QPoint(70, yPosition);
        QRectF rect = QRectF(0, 0, 30, BoardField::defaultWidthHeight);
        drawBoardFrameAtPosition(point, rect, numberTitles[i]);
    }

    for (int i = 0; i< numberOfRowsColumns; i++ ) {
        int xPosition = startXPosition + numberOfRowsColumns * BoardField::defaultWidthHeight;
        int yPosition = startYPosition + i * BoardField::defaultWidthHeight;
        QPoint point = QPoint(xPosition, yPosition);
        QRectF rect = QRectF(0, 0, 30, BoardField::defaultWidthHeight);
        drawBoardFrameAtPosition(point, rect, numberTitles[i]);
    }
}

void BoardView::drawBoardFrameAtPosition(QPoint point, QRectF rect, QString title) {
    BoardFrameField  *frameField = new BoardFrameField(this);

    frameField->setRect(rect);
    frameField->setPos(point);
    frameField->setTitle(title);
}

void BoardView::drawCheckWarningTextItems() {
    checkWarningTitleTextItem = Utils::createTextItem("This move is not possible!", 18, Constants::defaultTextColor, this);
    double titleXPosition = startXPosition + (BoardField::defaultWidthHeight*numberOfRowsColumns)/2 - checkWarningTitleTextItem->boundingRect().width()/2;
    double titleYPosition = startYPosition + (BoardField::defaultWidthHeight*numberOfRowsColumns) + 40;
    checkWarningTitleTextItem->setPos(titleXPosition, titleYPosition);
    checkWarningTitleTextItem->setOpacity(0);

    checkWarningDescriptionTextItem = Utils::createTextItem("You cannot make any move that places your own king in check", 18, Constants::defaultTextColor, this);
    double descriptionXPosition = startXPosition + (BoardField::defaultWidthHeight*numberOfRowsColumns)/2 - checkWarningDescriptionTextItem->boundingRect().width()/2;
    double descriptionYPosition = startYPosition + (BoardField::defaultWidthHeight*numberOfRowsColumns) + 60;
    checkWarningDescriptionTextItem->setPos(descriptionXPosition, descriptionYPosition);
    checkWarningDescriptionTextItem->setOpacity(0);
}

QPointF BoardView::getCoordinatesForBoardPosition(BoardPosition position) {
    int xPosition = startXPosition + position.x*BoardField::defaultWidthHeight;
    int yPosition = startYPosition + position.y*BoardField::defaultWidthHeight;

    return QPointF(xPosition, yPosition);
}
