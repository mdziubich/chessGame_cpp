#ifndef BOARDVIEWMODEL_H
#define BOARDVIEWMODEL_H

#include <QPoint>
#include "boardposition.h"

class BoardViewModel {

public:
    BoardViewModel();

    QPointF getCoordinatesForBoardPosition(BoardPosition position);
    bool validatePawnPalcementForMousePosition(QPoint position);
    BoardPosition getBoardPositionForMousePosition(QPoint position);
};

#endif // BOARDVIEWMODEL_H
