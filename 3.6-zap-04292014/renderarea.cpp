#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent),
      penProposedPath(QPen(Qt::blue)), penAxes(QPen(QColor(193,97,0))),
      penCoveredPath(QPen(QColor(60,196,70), 2)),
      penCurrPosActive(QPen(Qt::red, 6)), penCurrPosInactive(QPen(QColor(60,196,70), 6)),
      penMeasure(QPen(QColor(151,111,26))), isLiveCurrPos(false)
{
    penCurrPosActive.setCapStyle(Qt::RoundCap);
    penCurrPosInactive.setCapStyle(Qt::RoundCap);
}

void RenderArea::setItems(QList<PosItem> itemsRcvd)
{
    items = itemsRcvd;

    listToRender.setCurrFileLine(0);
    listToRender.convertList(items);
    listToRender.updateLivePoint();
    update();
}

void RenderArea::setLivePoint(double x, double y, bool mm, bool isLiveCP)
{
    isLiveCurrPos = isLiveCP;
    livePoint.setCoords(x, y, mm);
    listToRender.setLivePoint(livePoint);
    update();

}

void RenderArea::setVisualLivenessCurrPos(bool isLiveCP)
{
    isLiveCurrPos = isLiveCP;
}

void RenderArea::setVisCurrLine(int currLine)
{
    if (listToRender.setCurrFileLine(currLine))
        update();
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    if (!items.size())
        return;

    QSize size = this->size();

    listToRender.rescale(size);

    QPainter painter(this);

    painter.setPen(penProposedPath);
    listToRender.writePath(painter, false);

    painter.setPen(penAxes);
    listToRender.drawAxes(painter);

    painter.setPen(penMeasure);
    listToRender.drawMeasurements(painter);

    painter.setPen(penCoveredPath);
    listToRender.writePath(painter, true);

    //if (!livePoint.isNull()) FIX isNull
    {
        if (isLiveCurrPos)
            painter.setPen(penCurrPosActive);
        else
            painter.setPen(penCurrPosInactive);
        listToRender.drawPoint(painter, livePoint);
    }
}
