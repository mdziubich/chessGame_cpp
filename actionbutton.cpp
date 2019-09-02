#include "actionbutton.h"
#include <QBrush>
#include <QGraphicsRectItem>
#include <QFont>
#include "constants.h"
#include "utils.h"

ActionButton::ActionButton(QString title) {
    setRect(0, 0, 200, 50);

    QColor backgroundColor = QColor(157, 128, 101);
    Utils::setBackgroundColor(backgroundColor, this);

    QColor textColor = QColor(44, 41, 51);
    QGraphicsTextItem *text = Utils::createTextItem(title, 20, textColor, this);
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
