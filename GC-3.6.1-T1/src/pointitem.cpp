#include "pointitem.h"

PointItem::PointItem(double x1, double y1)
    : ItemToBase(0), x(x1), y(y1)
{
}

void PointItem::moveToFirst(QPainterPath& path)
{
    Q_UNUSED(path);
}

void PointItem::addToPath(QPainterPath& path)
{
    Q_UNUSED(path);
}

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
