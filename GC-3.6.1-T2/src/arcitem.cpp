#include "arcitem.h"

ArcItem::ArcItem(double sx1, double sy1, double ex1, double ey1, double centx1, double centy1, bool cw1, int index1)
    : ItemToBase(index1), sx(sx1), sy(sy1), ex(ex1), ey(ey1), centx(centx1), centy(centy1), cw(cw1), radius(0), angleStart(0), angleDelta(0)
{
}

PosItem ArcItem::computeExtents()
{
    PosItem extents(sx, sy, ex, ey);

    radius = qSqrt(((sx - centx) * (sx - centx)) + ((sy - centy) * (sy - centy)));

    if (cw)
    {
        double angle1 = qAtan2(ey - centy, ex - centx);
        double angle2 = qAtan2(sy - centy, sx - centx);

        if (angle1 > 0 && angle2 < 0)
            angle2 += TWO_PI;

        angleStart = angle2;
        angleDelta = angle1 - angle2;
    }
    else
    {
        double angle1 = qAtan2(sy - centy, sx - centx);
        double angle2 = qAtan2(ey - centy, ex - centx);

        if (angle1 > 0 && angle2 < 0)
            angle2 += TWO_PI;

        angleStart = angle2;
        angleDelta = angle1 - angle2;
    }

    // sample points along the curve
    double angleEnd = angleStart + angleDelta;
    for (double angle = angleStart;
         (angleDelta < 0 ? angle > angleEnd : angle < angleEnd);
         angle += (angleDelta < 0 ? -0.4 : 0.4))
    {
        double x = qCos(angle) * radius + centx;
        double y = qSin(angle) * radius + centy;

        PosItem curr(x, y, x, y);

        // expand rectange if it exceeds our last rectangle
        extents.expand(curr);
    }

    return extents;
}

void ArcItem::addToPath(QPainterPath& path)
{
    // need to convert our coordinates into arcTo arguments (rectangle boxes and angles, etc.)
    // Also, we are at this point in screen coordinates, not machine coordinates, i.e. Y positive is down!

    // first, we know for a fact that we are dealing with a circular arc, not an ellipse
    // (code could be put here to verify that is true)
    // Thus our radius is also our bounding box determined from the center of the arc/circle

    if (cw)
    {
        path.moveTo(screenX(sx), screenY(sy));
    }
    else
    {
        path.moveTo(screenX(ex), screenY(ey));
    }

    double x = centx - radius;
    double y = centy + radius;
    double wd = radius * 2;
    double ht = wd;

    double fx = screenX(x);
    double fy = screenY(y);
    double w = wd * scale;
    double h = ht * scale;

    double angleStartDeg = toDegrees(angleStart);
    double angleDeltaDeg = toDegrees(angleDelta);

    path.arcTo(fx, fy, w, h, angleStartDeg, angleDeltaDeg);

    path.moveTo(screenX(ex), screenY(ey));
}

void ArcItem::moveToFirst(QPainterPath& path)
{
    // not applicable! generate error!
    Q_UNUSED(path);
}

double ArcItem::getXScr()
{
    return screenX(ex);
}

double ArcItem::getYScr()
{
    return screenY(ey);
}

double ArcItem::getXRaw()
{
    return ex;
}

double ArcItem::getYRaw()
{
    return ey;
}

double ArcItem::toDegrees(double rad)
{
    return 360 * rad / TWO_PI;
}
