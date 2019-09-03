#ifndef CONGRATULATIONSVIEW_H
#define CONGRATULATIONSVIEW_H

#include <QGraphicsRectItem>
#include "basepawnmodel.h"

class CongratulationsView: public QObject, public QGraphicsRectItem {
    Q_OBJECT

public:
    CongratulationsView(PlayerType winner);
};

#endif // CONGRATULATIONSVIEW_H
