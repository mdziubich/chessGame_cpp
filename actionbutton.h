#ifndef ACTIONBUTTON_H
#define ACTIONBUTTON_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>

class ActionButton: public QObject, public QGraphicsRectItem  {
    Q_OBJECT
public:
    ActionButton(QString title);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
    void buttonPressed();

private:
    void setBackgroundColor(Qt::GlobalColor color);
};

#endif // ACTIONBUTTON_H
