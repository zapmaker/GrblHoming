#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPen>
#include <QPainter>

#include "positem.h"
#include "renderitemlist.h"
#include "arcitem.h"
#include "lineitem.h"

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = 0);

signals:

public slots:
    void setItems(QList<PosItem>);
    void setLivePoint(double x, double y, bool isMM, bool isLiveCP);
    void setVisualLivenessCurrPos(bool isLiveCP);
    void setVisCurrLine(int currLine);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QList<PosItem> items;
    RenderItemList listToRender;
    QPen penProposedPath, penAxes, penCoveredPath, penCurrPosActive, penCurrPosInactive, penMeasure;
    PosItem livePoint;
    bool isLiveCurrPos;
};

#endif // RENDERAREA_H
