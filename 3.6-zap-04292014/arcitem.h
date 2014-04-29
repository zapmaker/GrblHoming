#ifndef ARCITEM_H
#define ARCITEM_H
#include <QtCore>
#include "itemtobase.h"

#define TWO_PI  (2 * 3.1415926)

class ArcItem : public ItemToBase
{
public:
    ArcItem(double sx1, double sy1, double ex1, double ey1, double centx1, double centy1, bool cw, int index);

    void moveToFirst(QPainterPath& path);
    void addToPath(QPainterPath& path);
    PosItem computeExtents();

    double getXScr();
    double getYScr();
    double getXRaw();
    double getYRaw();

    double toDegrees(double rad);

private:
    double sx;
    double sy;
    double ex;
    double ey;
    double centx;
    double centy;
    bool cw;

    double radius;
    double angleStart;
    double angleDelta;

};

#endif // ARCITEM_H
