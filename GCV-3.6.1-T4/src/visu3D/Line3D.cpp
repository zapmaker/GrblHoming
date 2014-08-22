/***************************************************************
 * Name: Line3D.cpp
 * Purpose:
 * Author:    LETARTARE
 * Created:   2014-16-06
 * Copyright: LETARTARE
 * License:   GPL
 **************************************************************/

#include "Line3D.h"

#include <QtOpenGL>
#include "definitions.h"

Line3D::Line3D() :
	pstart(), pend(),
	color (Qt::black),
	feedrate(SPEED_DEFAULT)

{
}

Line3D::Line3D( const QVector3D s, const QVector3D e) :
        pstart(s),
        pend(e),
        color(Qt::blue), linewidth(1),
        feedrate(SPEED_DEFAULT)
{
}

Line3D::~Line3D()
{
	//dtor
}

void Line3D::gdraw3D() const
{
	glLineWidth(linewidth);
    glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
    glBegin(GL_LINES);
		glVertex3d(pstart.x(), pstart.y(), pstart.z());
		glVertex3d(pend.x(), pend.y(), pend.z());
    glEnd();
}

void Line3D::setColor(QColor c)
{
    color = c ;
}

void Line3D::setLineWidth(int lw)
{
	if (lw > 0 && lw <= 10)
		linewidth = lw;
	else
		linewidth = 1;
}

void Line3D::setSpeed (double f)
{
	if (f > SPEED_MIN && f <= SPEED_MAX)
		feedrate = f;
}

void Line3D::MinMax(QVector3D& pmin, QVector3D& pmax)
{
	/// start point
	double x = pstart.x(), y = pstart.y(), z = pstart.z();
	if (x > pmax.x()) pmax.setX(x);
	if (y > pmax.y()) pmax.setY(y);
	if (z > pmax.z()) pmax.setZ(z);

	if (x < pmin.x()) pmin.setX(x);
	if (y < pmin.y()) pmin.setY(y);
	if (z < pmin.z()) pmin.setZ(z);
	/// end point
	x = pend.x(), y = pend.y(), z = pend.z();
	if (x > pmax.x()) pmax.setX(x);
	if (y > pmax.y()) pmax.setY(y);
	if (z > pmax.z()) pmax.setZ(z);

	if (x < pmin.x()) pmin.setX(x);
	if (y < pmin.y()) pmin.setY(y);
	if (z < pmin.z()) pmin.setZ(z);
}
