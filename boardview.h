#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QGraphicsRectItem>
#include <QList>
#include <QPoint>
#include "boardfield.h"
#include "pawnfield.h"

class BoardView: public QGraphicsRectItem {

public:
    BoardView();

    static int numberOfRowsColumns;
    static int startXPosition;
    static int startYPosition;

    QList<BoardField*> getFields();
    void draw();
    void initializePawnFields(QList<PawnModel*> pawns);
    PawnField* getPawnAtBoardPosition(BoardPosition boardPosition);
    PawnField* getPawnAtMousePosition(QPoint point);
    void moveActivePawnToMousePosition(QPoint point, PawnModel *pawn);
    void placeActivePawnAtBoardPosition(PawnModel *pawn, BoardPosition boardPosition);
    void removePawnAtBoardPosition(BoardPosition boardPosition);
    void setPawnMoveCheckWarning(bool visible);
    void promotePawnAtBoardPosition(BoardPosition boardPosition);

private:
    QList<BoardField*> fields;
    QList<PawnField*> pawns;
    QGraphicsTextItem *checkWarningTitleTextItem;
    QGraphicsTextItem *checkWarningDescriptionTextItem;

    void placeBoardFields();
    void createFieldsColumn(int xPosition, int columnNumber);
    void drawBoardFrame();
    void drawBoardFrameAtPosition(QPoint point, QRectF rect, QString title);
    void drawCheckWarningTextItems();
    QPointF getCoordinatesForBoardPosition(BoardPosition position);
};

#endif // BOARDVIEW_H
