#include "boardview.h"
#include <boardfield.h>
#include <game.h>

extern Game *game;

BoardView::BoardView() {
}

void BoardView::draw() {
    placeBoardFields();
    placePawns();
}

QList<BoardField*> BoardView::getFields() {
    return fields;
}

void BoardView::placeBoardFields() {
    int numberOfColumns = 8;
    int startXPosition = 100;
    int yPosition = 100;

    for (int i = 0; i< numberOfColumns; i++ ) {
        int xPosition = startXPosition + (i * BoardField::defaultHeight);
        createFeildsColumn(xPosition, yPosition, numberOfColumns, i);
    }
}

// creates a column of fields at the specified location with specified number of rows
void BoardView::createFeildsColumn(int xPosition, int yPosition, int numberOfRows, int columnNumber) {
    for (int rowNumber = 0, n = numberOfRows; rowNumber < n; rowNumber++) {
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

        BoardField *field = new BoardField(backgroundColor);
        int filedYPosition = yPosition + (rowNumber * field->defaultHeight);
        field->setPos(xPosition, filedYPosition);
        fields.append(field);
        game->scene->addItem(field);
    }
}

void BoardView::placePawns() {

}
