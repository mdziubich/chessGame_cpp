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

    void placeBoardFields();
    void createFeildsColumn(int xPosition, int yPosition, int numberOfRows);
    void placePawns();
};

#endif // BOARDVIEW_H
