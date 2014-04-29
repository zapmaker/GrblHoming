#include "itemtobase.h"

ItemToBase::ItemToBase(int index1)
    : scale(1), height(100), offsetx(50), offsety(50), index(index1)
{
}

ItemToBase::~ItemToBase()
{
}

void ItemToBase::setParams(double scale1, double height1, double offsetx1, double offsety1)
{
    scale = scale1;
    height = height1;
    offsetx = offsetx1;
    offsety = offsety1;
}

double ItemToBase::screenX(double fx)
{
    return (fx * scale) + offsetx;
}

double ItemToBase::screenY(double fy)
{
    return height - ((fy * scale) + offsety);
}
