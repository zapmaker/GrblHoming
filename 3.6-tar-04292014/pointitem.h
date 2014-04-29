#ifndef POINTITEM_H
#define POINTITEM_H
#include "itemtobase.h"

class PointItem : public ItemToBase
{
public:
    PointItem(double x, double y);

    void moveToFirst(QPainterPath& path);
    void addToPath(QPainterPath& path);
    PosItem computeExtents();
    double getXScr();
    double getYScr();
    double getXRaw();
    double getYRaw();

private:
    double x;
    double y;
};

#endif // POINTITEM_H
