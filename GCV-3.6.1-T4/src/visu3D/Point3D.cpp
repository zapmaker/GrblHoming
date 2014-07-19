/***************************************************************
 * Name:    Point3D.cpp
 * Purpose:
 * Author:    LETARTARE
 * Created:   2014-16-06
 * Copyright: LETARTARE
 * License:   GPL
 **************************************************************/

#include "Point3D.h"
#include <QtOpenGL>

Point3D::Point3D() :
	p(),
	color (Qt::black)
{
}

Point3D::Point3D(const QColor c, const QVector3D s) :
        p(s),
        color(c)
{
}

Point3D::~Point3D()
{   //dtor
}

void Point3D::setColor(QColor c)
{
    color = c ;
}

void Point3D::gdraw3D() const
{
	glLineWidth(1);
    glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
    glBegin(GL_POINTS);
		glVertex3d(p.x(), p.y(), p.z());
    glEnd();
}

void Point3D::MinMax(QVector3D& pmin, QVector3D& pmax)
{
	/// start point
	double x = p.x(), y = p.y(), z = p.z();
	if (x > pmax.x()) pmax.setX(x);
	if (y > pmax.y()) pmax.setY(y);
	if (z > pmax.z()) pmax.setZ(z);

	if (x < pmin.x()) pmin.setX(x);
	if (y < pmin.y()) pmin.setY(y);
	if (z < pmin.z()) pmin.setZ(z);
}
