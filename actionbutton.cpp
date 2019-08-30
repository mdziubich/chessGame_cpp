#include "actionbutton.h"
#include <QBrush>
#include <QGraphicsRectItem>
#include <QFont>
#include <utils.h>

ActionButton::ActionButton(QString title) {
    setRect(0, 0, 200, 50);

    QColor backgroundColor = QColor(157, 128, 101);
    Utils::setBackgroundColor(backgroundColor, this);

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
    emit buttonPressed();
}

void ActionButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    QColor backgroundColor = QColor(196, 178, 140);
    Utils::setBackgroundColor(backgroundColor, this);
}

void ActionButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    QColor backgroundColor = QColor(157, 128, 101);
    Utils::setBackgroundColor(backgroundColor, this);
}
