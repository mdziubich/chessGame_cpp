#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QGraphicsRectItem>
#include <QList>
#include <QPoint>
#include "boardfield.h"
#include "pawn.h"

class BoardView: public QGraphicsRectItem {

public:
    BoardView();

    static int numberOfRowsColumns;
    static int startXPosition;
    static int startYPosition;

    QList<BoardField*> getFields();
    void draw();
    Pawn* getPawnAtBoardPosition(BoardPosition boardPosition);
    Pawn* getPawnAtMousePosition(QPoint point);
    void placePawnAtBoardPosition(Pawn *pawn, BoardPosition boardPosition);
    void moveActivePawnToMousePosition(QPoint point, Pawn *pawn);

private:
    QList<BoardField*> fields;
    QList<Pawn*> pawns;

    void placeBoardFields();
    void createFieldsColumn(int xPosition, int columnNumber);
    void placePawns();
    void placePawnsForRow(int rowNumber);
};

#endif // BOARDVIEW_H
