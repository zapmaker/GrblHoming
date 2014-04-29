#ifndef RENDERITEMLIST_H
#define RENDERITEMLIST_H
#include "arcitem.h"
#include "lineitem.h"
#include "pointitem.h"

#define SCREEN_SCALE_FILE   0.85

class RenderItemList
{
public:
    RenderItemList();
    virtual ~RenderItemList();

    void convertList(const QList<PosItem>& items);
    void rescale(const QSize& size);
    void writePath(QPainter& painter, bool updatedFromFile);
    void drawAxes(QPainter& painter);
    void drawMeasurements(QPainter& painter);
    void drawPoint(QPainter& painter, const PosItem& point);
    bool setCurrFileLine(const int currLine);
    void setLivePoint(const PosItem& livePoint);
    void updateLivePoint();

private:
    void clearList();
    void writeText(QPainter& painter, QString text, double x, double y, int avgCharWd);

private:
    QList<ItemToBase *> list;
    double scale;
    double offsetx;
    double offsety;
    PosItem extents;
    QSize windowSize;
    bool mm;
    int currFileLine;
    PosItem livePoint;
    QFont font;
};

#endif // RENDERITEMLIST_H
