#include "positem.h"

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

void PosItem::toMm()
{
    x *= MM_IN_AN_INCH;
    y *= MM_IN_AN_INCH;
    i *= MM_IN_AN_INCH;
    j *= MM_IN_AN_INCH;
    mm = true;
}

void PosItem::toInches()
{
    x /= MM_IN_AN_INCH;
    y /= MM_IN_AN_INCH;
    i /= MM_IN_AN_INCH;
    j /= MM_IN_AN_INCH;
    mm = false;
}
