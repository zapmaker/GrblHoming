/***************************************************************
 * Name: Line3D.h
 * Purpose:
 * Author:    LETARTARE
 * Created:   2014-16-06
 * Copyright: LETARTARE
 * License:   GPL
 **************************************************************/

#ifndef LINE3D_H
#define LINE3D_H

#include <QtGui>

/*!
  A simple line 3D.
  */
class Line3D
{
public:
	Line3D();

    Line3D(const QVector3D s, const QVector3D e) ;

    virtual ~Line3D();

    void gdraw3D() const;

    void setColor (QColor);

    void setLineWidth(int);

    void setSpeed (double);

    void MinMax(QVector3D&, QVector3D&);

private:

    QVector3D pstart, pend;
    QColor color;
    int linewidth;
    double speed;

};

#endif // LINE3D_H


