#ifndef PAWNMANAGER_H
#define PAWNMANAGER_H

#include <QString>
#include "basepawnmodel.h"

class PawnViewModel {

public:

    PawnViewModel();

    QString getImagePath(PawnType type, PlayerType owner);
    PawnType getTypeForInitialPosition(BoardPosition position);
};

#endif // PAWNMANAGER_H
