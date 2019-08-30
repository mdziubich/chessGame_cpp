#ifndef UTILS_H
#define UTILS_H

#include <QAbstractGraphicsShapeItem>
#include <QColor>

class Utils {

public:
    static void setBackgroundColor(QColor color, QAbstractGraphicsShapeItem *item);
};

#endif // UTILS_H
