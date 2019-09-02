#ifndef UTILS_H
#define UTILS_H

#include <QAbstractGraphicsShapeItem>
#include <QColor>

class Utils {

public:
    static void setBackgroundColor(QColor color, QAbstractGraphicsShapeItem *item);
    static void setImage(QString imagePath, QGraphicsRectItem *item);
    static QGraphicsTextItem* createTextItem(QString title, int fontSize, QColor textColor, QGraphicsItem *parent = nullptr);
};

#endif // UTILS_H
