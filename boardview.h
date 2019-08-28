#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QList>
#include <boardfield.h>

class BoardView {

public:
    BoardView();

    void draw();
    QList<BoardField*> getFields();

private:
    QList<BoardField*> fields;
    int numberOfColumns;

    void placeBoardFields();
    void createFeildsColumn(int xPosition, int yPosition, int numberOfRows, int columnNumber);
    void placePawns();
    void placePawnsForRow(int rowNumber);
};

#endif // BOARDVIEW_H
