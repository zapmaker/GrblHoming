#include "renderitemlist.h"
#include <QObject>

RenderItemList::RenderItemList()
    : scale(1), offsetx(50), offsety(50), mm(true), currFileLine(0)
{
    font.setStyleHint(QFont::Courier);
    font.setPointSize(10);
}

RenderItemList::~RenderItemList()
{
    clearList();
}

void RenderItemList::clearList()
{
    while (!list.isEmpty())
        delete list.takeFirst();
}

void RenderItemList::convertList(const QList<PosItem>& items)
{
    clearList();

    if (items.size() == 0)
        return;

    double lastx = items.at(0).x, lasty = items.at(0).y;
    mm = items.at(0).mm;
    foreach (PosItem item, items)
    {
        if (item.arc)
        {
            double px = lastx + item.i;
            double py = lasty + item.j;
            double sx = lastx;
            double sy = lasty;
            double ex = item.x;
            double ey = item.y;

            list.append(new ArcItem(
                               sx, sy, ex, ey, px, py, item.cw, item.index));
        }
        else
        {
            double sx = item.x;
            double sy = item.y;

            list.append(new LineItem(sx, sy, item.index));
        }

        lastx = item.x;
        lasty = item.y;
    }

    extents.setCoords(0,0,0,0);
    foreach (ItemToBase *item, list)
    {
        PosItem e = item->computeExtents();

        // can't use QRectF because it reverses the y axis in anticipation of screendraws, which we don't want
        //extents = extents.united(e);

        extents.expand(e);
    }
}

void RenderItemList::rescale(const QSize& size)
{
    PosItem liveExtents(extents);
    liveExtents.expand(livePoint);

    double scalex = SCREEN_SCALE_FILE * (size.width() / (liveExtents.width()));
    double scaley = SCREEN_SCALE_FILE * (size.height() / (liveExtents.height()));

    scale = qMin(scalex, scaley);

    offsetx = size.width() / 2 - ((liveExtents.x + liveExtents.i) / 2) * scale;
    offsety = size.height() / 2 - ((liveExtents.y + liveExtents.j) / 2) * scale;

    windowSize = size;
}

void RenderItemList::writePath(QPainter& painter, bool updatedFromFile)
{
    QPainterPath path;
    ItemToBase *item = list.at(0);
    item->setParams(scale, windowSize.height(), offsetx, offsety);
    item->moveToFirst(path);
    foreach (item, list)
    {
        if (updatedFromFile)
        {
            if (item->getIndex() > currFileLine)
                break;
        }

        item->setParams(scale, windowSize.height(), offsetx, offsety);
        item->addToPath(path);
    }

    painter.drawPath(path);
}

void RenderItemList::drawAxes(QPainter& painter)
{
    QPainterPath path;

    ItemToBase *item = list.at(0);
    double x = item->getXScr();
    double y = item->getYScr();

    path.moveTo(x, 0);
    path.lineTo(x, windowSize.height() - 1);
    path.moveTo(0, y);
    path.lineTo(windowSize.width() - 1, y);

    painter.drawPath(path);
}

void RenderItemList::drawMeasurements(QPainter& painter)
{
    QPainterPath path;

    ItemToBase *item = list.at(0);
    double x = item->getXScr();
    double y = item->getYScr();
    double xr = item->getXRaw();
    double yr = item->getYRaw();

    const int length = 6;
    LineItem x1(extents.x, yr, true, length);
    x1.setParams(scale, windowSize.height(), offsetx, offsety);
    x1.drawTo(path);

    LineItem x2(extents.i, yr, true, length);
    x2.setParams(scale, windowSize.height(), offsetx, offsety);
    x2.drawTo(path);

    LineItem y1(xr, extents.y, false, length);
    y1.setParams(scale, windowSize.height(), offsetx, offsety);
    y1.drawTo(path);

    LineItem y2(xr, extents.j, false, length);
    y2.setParams(scale, windowSize.height(), offsetx, offsety);
    y2.drawTo(path);

    painter.drawPath(path);

    painter.setFont(font);

    int ht = painter.fontMetrics().height();
    int wd = painter.fontMetrics().averageCharWidth();

    QString units = mm ? QObject::tr(" mm") : QObject::tr(" inches");

    QString info(QString::number(extents.j).append(units).append(QObject::tr("  (Width-X: ").append(QString::number(extents.width()))
                .append(QObject::tr("  Height-Y: ")).append(QString::number(extents.height())).append(")")) )  ;
    int xMsgTop = x + wd;
    QRect br = painter.fontMetrics().boundingRect(info);
    br.setWidth(br.width() + wd);
    if (br.width() > (windowSize.width() - x))
        xMsgTop = wd;

#ifdef Q_OS_MACX
    writeText(painter, info, xMsgTop, (3 * ht / 4) + 4, wd);
#else
    writeText(painter, info, xMsgTop, (3 * ht / 4) + 1, wd);
#endif

#ifdef Q_OS_MACX
    writeText(painter, QString::number(extents.y), x + wd, windowSize.height() - (ht / 2) - 1, wd);
#else
    writeText(painter, QString::number(extents.y), x + wd, windowSize.height() - (ht / 4) - 1, wd);
#endif

    writeText(painter, QString::number(extents.x), wd, y - (ht / 4), wd);

    QString right = QString::number(extents.i);
    br = painter.fontMetrics().boundingRect(right);
    writeText(painter, right, windowSize.width() - (br.width() + wd), y - (ht / 4), wd);
}

void RenderItemList::writeText(QPainter& painter, QString text, double x, double y, int avgCharWd)
{
    // We need to clear a rectangle into which our text will be written so it is easier to read
    QRect br = painter.fontMetrics().boundingRect(text);
    br.setWidth(br.width() + avgCharWd);
    br.translate(x, y);
    // TODO: get the background color from the window instead, otherwise
    // any changes to it need to be changed here
    painter.fillRect(br, QColor(244,237,187));
    painter.drawText(x, y, text);
}

void RenderItemList::drawPoint(QPainter& painter, const PosItem& point)
{
    double divisor = 1;
    if ((mm && !point.mm) || (!mm && point.mm))
        divisor = MM_IN_AN_INCH;

    PointItem p(point.x / divisor, point.y / divisor);

    p.setParams(scale, windowSize.height(), offsetx, offsety);

    painter.drawPoint(p.getXScr(), p.getYScr());

}

bool RenderItemList::setCurrFileLine(const int currLine)
{
    currFileLine = currLine;
    foreach (ItemToBase *item, list)
    {
        if (item->getIndex() == currLine)
            return true;
        else if (item->getIndex() > currLine)
            return false;
    }
    return false;
}

void RenderItemList::setLivePoint(const PosItem& livePoint1)
{
    livePoint = livePoint1;

    updateLivePoint();
}

void RenderItemList::updateLivePoint()
{
    if (mm && !livePoint.mm)
    {
        livePoint.toMm();
    }
    else if (!mm && livePoint.mm)
    {
        livePoint.toInches();
    }
}
