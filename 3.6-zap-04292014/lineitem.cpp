#include "lineitem.h"

LineItem::LineItem(double x1, double y1, int index1)
    : ItemToBase(index1), x(x1), y(y1)
{
}

LineItem::LineItem(double x1, double y1, bool stretchX1, double length1)
: ItemToBase(0), x(x1), y(y1), stretchX(stretchX1), length(length1)
{
}

PosItem LineItem::computeExtents()
{
    PosItem curr(x, y, x, y);
    return curr;
}

void LineItem::addToPath(QPainterPath& path)
{
    path.lineTo(screenX(x), screenY(y));
}

void LineItem::moveToFirst(QPainterPath& path)
{
    path.moveTo(screenX(x), screenY(y));
}

double LineItem::getXScr()
{
    return screenX(x);
}

double LineItem::getYScr()
{
    return screenY(y);
}

double LineItem::getXRaw()
{
    return x;
}

double LineItem::getYRaw()
{
    return y;
}

void LineItem::drawTo(QPainterPath& path)
{
    if (stretchX)
    {
        path.moveTo(screenX(x), screenY(y) + length);
        path.lineTo(screenX(x), screenY(y) - length);
    }
    else
    {
        path.moveTo(screenX(x) + length, screenY(y));
        path.lineTo(screenX(x) - length, screenY(y));
    }
}
