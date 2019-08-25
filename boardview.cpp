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
    int numberOfRows = 8;
    int startXPosition = 100;
    int yPosition = 100;

    for (int i = 0; i< numberOfRows; i++ ) {
        int xPosition = startXPosition + (i * BoardField::defaultHeight);
        createFeildsColumn(xPosition, yPosition, numberOfRows);
    }
}

// creates a column of fields at the specified location with specified number of rows
void BoardView::createFeildsColumn(int xPosition, int yPosition, int numberOfRows) {
    for (int i = 0, n = numberOfRows; i < n; i++) {
        BoardField *field = new BoardField();
        int filedYPosition = yPosition + (i * field->defaultHeight);
        field->setPos(xPosition, filedYPosition);
        fields.append(field);
        game->scene->addItem(field);
    }
}

void BoardView::placePawns() {

}
