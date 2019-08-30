#ifndef BOARDFRAMEFIELD_H
#define BOARDFRAMEFIELD_H

#include <QGraphicsRectItem>

class BoardFrameField: public QGraphicsRectItem  {

public:
    BoardFrameField(QGraphicsItem *parent = nullptr);

    void setTitle(QString title);
};

#endif // BOARDFRAMEFIELD_H
