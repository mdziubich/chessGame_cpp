#include "utils.h"
#include <QBrush>
#include <QLabel>
#include <QGraphicsProxyWidget>

void Utils::setBackgroundColor(QColor color, QAbstractGraphicsShapeItem *item) {
    QBrush brush;
    brush.setStyle((Qt::SolidPattern));
    brush.setColor(color);
    item->setBrush(brush);
}

void Utils::setImage(QString imagePath, QGraphicsRectItem *item) {
    QPixmap image(imagePath);
    QLabel *imageLabel = new QLabel();
    QGraphicsProxyWidget *pMyProxy = new QGraphicsProxyWidget(item);

    imageLabel->setPixmap(image);
    imageLabel->setAttribute(Qt::WA_TranslucentBackground);
    pMyProxy->setWidget(imageLabel);
}

QGraphicsTextItem* Utils::createTextItem(QString title, int fontSize, QColor textColor, QGraphicsItem *parent) {
    QGraphicsTextItem *textItem = new QGraphicsTextItem(title, parent);
    QFont titleFont("avenir", fontSize);
    textItem->setDefaultTextColor(textColor);
    textItem->setFont(titleFont);

    return textItem;
}
