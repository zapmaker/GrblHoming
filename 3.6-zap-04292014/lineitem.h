#ifndef LINEITEM_H
#define LINEITEM_H
#include "itemtobase.h"

class LineItem : public ItemToBase
{
public:
    LineItem(double x1, double y1, int index);
    LineItem(double x1, double y1, bool stretchX, double length);

    void moveToFirst(QPainterPath& path);
    void addToPath(QPainterPath& path);
    PosItem computeExtents();

    void drawTo(QPainterPath& path);

    double getXScr();
    double getYScr();
    double getXRaw();
    double getYRaw();

private:
    double x;
    double y;
    bool stretchX;
    double length;
};

#endif // LINEITEM_H
