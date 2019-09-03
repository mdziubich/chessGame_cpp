#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include "basepawnmodel.h"

class PlayerView: public QGraphicsRectItem  {

public:
    PlayerView(QGraphicsItem *parent = nullptr);

    static int defaultWidthHeight;

    void setPlayer(PlayerType owner);
    void setActive(bool active);
    void setIsInCheck(bool isCheck);

private:
    QGraphicsTextItem *checkTextItem;
};

#endif // PLAYERVIEW_H
