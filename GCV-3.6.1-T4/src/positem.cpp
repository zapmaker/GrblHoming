#include "positem.h"

/// 2 axes
void PosItem::setCoords(double x1, double y1, double i1, double j1)
{
    x = x1;
    y = y1;
    i = i1;
    j = j1;
}

void PosItem::setCoords(double x1, double y1, bool mm1)
{
    x = x1;
    y = y1;
    i = x1;
    j = y1;
    mm = mm1;
}

void PosItem::expand(const PosItem& item)
{
    if (item.x < x)
        x = item.x;
    if (item.y < y)
        y = item.y;
    if (item.i > i)
        i = item.i;
    if (item.j > j)
        j = item.j;
}

/// 3 axes
void PosItem::setCoords(double x1, double y1, double z1, double i1, double j1, double k1)
{
    x = x1;
    y = y1;
    z = z1;
    i = i1;
    j = j1;
    k = k1;
}
/// 3 axes
void PosItem::setCoords(QVector3D xyz, QVector3D ijk)
{
    x = xyz.x();
    y = xyz.y();
    z = xyz.z();
    i = ijk.x();
    j = ijk.y();
    k = ijk.z();
}

void PosItem::setCoords(double x1, double y1, double z1, bool mm1)
{
    x = x1;
    y = y1;
    z = z1;
    i = x1;
    j = y1;
    k = z1;
    mm = mm1;
}

///-----------------------------------------------------------------------------
/// common 2 or 3 axes

void PosItem::toMm()
{
    x *= MM_IN_AN_INCH;
    y *= MM_IN_AN_INCH;
    z *= MM_IN_AN_INCH;
    i *= MM_IN_AN_INCH;
    j *= MM_IN_AN_INCH;
    k *= MM_IN_AN_INCH;
    mm = true;
}

void PosItem::toInches()
{
    x /= MM_IN_AN_INCH;
    y /= MM_IN_AN_INCH;
    z /= MM_IN_AN_INCH;
    i /= MM_IN_AN_INCH;
    j /= MM_IN_AN_INCH;
    k /= MM_IN_AN_INCH;
    mm = false;
}
