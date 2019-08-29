#include "boardviewmodel.h"
#include "boardview.h"
#include "boardfield.h"
#include <math.h>

BoardViewModel::BoardViewModel() {

}

QPointF BoardViewModel::getCoordinatesForBoardPosition(BoardPosition position) {
    int xPosition = BoardView::startXPosition + position.x*BoardField::defaultWidthHeight;
    int yPosition = BoardView::startYPosition + position.y*BoardField::defaultWidthHeight;

    return QPointF(xPosition, yPosition);
}

bool BoardViewModel::validatePawnPalcementForMousePosition(QPoint point) {
    if (point.x() > BoardView::startXPosition &&
            point.x() < (BoardView::startXPosition + BoardField::defaultWidthHeight*BoardView::numberOfRowsColumns) &&
            point.y() > BoardView::startYPosition &&
            point.y() < (BoardView::startYPosition + BoardField::defaultWidthHeight*BoardView::numberOfRowsColumns)) {
        return true;
    }
    return false;
}

BoardPosition BoardViewModel::getBoardPositionForMousePosition(QPoint point) {
    int xPosition = static_cast<int>(floor((point.x() - BoardView::startXPosition)/BoardField::defaultWidthHeight));
    int yPosition = static_cast<int>(floor((point.y() - BoardView::startYPosition)/BoardField::defaultWidthHeight));

    return BoardPosition { xPosition, yPosition };
}
