/***************************************************************
 * Name:    Box3D.h
 * Purpose:
 * Author:    LETARTARE
 * Created:   2014-20-06
 * Copyright: LETARTARE
 * License:   GPL
 **************************************************************/

#ifndef BOX3D_H
#define BOX3D_H

#include <QtGui>


// An Axis Aligned Bounding Box.
class Box3D
{
public:
	Box3D(const QVector3D p1, const QVector3D p2, QColor c = Qt::red);

	void gdraw3D() const;

	void setColor (QColor);

	void setDim (QVector3D p1, QVector3D p2);

private:

	QVector3D pmin, pmax;
	QColor color;

};

#endif
