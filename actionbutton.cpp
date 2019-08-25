#include "actionbutton.h"
#include <QBrush>
#include <QGraphicsRectItem>
#include <QFont>

ActionButton::ActionButton(QString title) {
    setRect(0, 0, 200, 50);
    setBackgroundColor(Qt::darkCyan);

    QGraphicsTextItem *text = new QGraphicsTextItem(title, this);
    QFont textFont("avenir", 20);
    text->setFont(textFont);
    double xPosition = rect().width()/2 - text->boundingRect().width()/2;
    double yPosition = rect().height()/2 - text->boundingRect().height()/2;

    text->setPos(xPosition, yPosition);

    // allow responding to hover events
    setAcceptHoverEvents(true);
}

void ActionButton::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit clicked();
}

void ActionButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    setBackgroundColor(Qt::cyan);
}

void ActionButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    setBackgroundColor(Qt::darkCyan);
}

void ActionButton::setBackgroundColor(Qt::GlobalColor color) {
    QBrush brush;
    brush.setStyle((Qt::SolidPattern));
    brush.setColor(color);
    setBrush(brush);
}
