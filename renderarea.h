#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPen>
#include <QPainter>

#include "positem.h"
#include "renderitemlist.h"
#include "arcitem.h"
#include "lineitem.h"
/// LETARTARE
// #include "renderitemlist.h"

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = 0);

signals:

public slots:
    void setItems(QList<PosItem>);
    void setLivePoint(double x, double y, bool isMM);
    void setVisCurrLine(int currLine);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QList<PosItem> items;
    RenderItemList listToRender;
    QPen penProposedPath, penAxes, penCoveredPath, penCurrPos, penMeasure;
    PosItem livePoint;
};

#endif // RENDERAREA_H
