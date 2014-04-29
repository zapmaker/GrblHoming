#include "pointitem.h"

PointItem::PointItem(double x1, double y1)
    : ItemToBase(0), x(x1), y(y1)
{
}

#pragma GCC diagnostic ignored "-Wunused-parameter" push
void PointItem::moveToFirst(QPainterPath& path)
{
}
#pragma GCC diagnostic ignored "-Wunused-parameter" pop

#pragma GCC diagnostic ignored "-Wunused-parameter" push
void PointItem::addToPath(QPainterPath& path)
{
}
#pragma GCC diagnostic ignored "-Wunused-parameter" pop

PosItem PointItem::computeExtents()
{
    return PosItem();
}

double PointItem::getXScr()
{
    return screenX(x);
}

double PointItem::getYScr()
{
    return screenY(y);
}

double PointItem::getXRaw()
{
    return x;
}

double PointItem::getYRaw()
{
    return y;
}
