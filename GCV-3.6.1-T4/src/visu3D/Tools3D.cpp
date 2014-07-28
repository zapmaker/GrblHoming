/***************************************************************
 * Name:    Tools3D.cpp
 * Purpose:
 * Author:    LETARTARE
 * Created:   2014-20-06
 * Copyright: LETARTARE
 * License:   GPL
 **************************************************************/

#include "Tools3D.h"

#include <QtOpenGL>
#include "definitions.h"


Tools3D::Tools3D() :
	color (Qt::black)
{
}

Tools3D::Tools3D(uint8_t pl, QVector3D s, typeTool t) :
	plane(pl),
	start(s),
	type(t),
	color (Qt::black),
	mm(true)
{
}

Tools3D::~Tools3D()
{
}

void Tools3D::setColor(QColor c)
{
    color = c ;
}

void Tools3D::setPlane(uint8_t pl)
{
	plane = pl;
}

void Tools3D::setPos(QVector3D pos)
{
	start = pos;
}

void Tools3D::setPos(qglviewer::Vec vpos)
{
	start = QVector3D(vpos.x, vpos.y, vpos.z) ;
}

void Tools3D::setPos(double x, double y, double z)
{
	start = QVector3D(x, y, z);;
}

/// just a red point
void Tools3D::setTool(typeTool t)
{
	type = t;
}
void Tools3D::setUnit(bool mm1)
{
	mm = mm1;
}

//
void Tools3D::gdraw3D() const
{
	float X = start.x();
	float Y = start.y();
	float Z = start.z();
	/// mm
	float D = 3.0;
	float L = 10.0;
	if (!mm) {
		D /= MM_IN_AN_INCH;
		L /= MM_IN_AN_INCH;
	}
	float R = D/2.0;
	float H = 3*D;

	QColor color(Qt::red);  color.setRgb(255, 90, 40, 255);
	glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
	// a quadratic object in the heap for caps
	GLUquadricObj * temp = gluNewQuadric ();
	glPushMatrix();
	{
		// placing the axis of the tool to the position 'X, Y, Z'
		glTranslated (X, Y, Z );
		if (plane == PLANE_XY_G17)  {
		// align the tool perpendicular to the work plan
			glRotated (180, 1, 0, 0);
		}
		else
		if (plane == PLANE_ZX_G19) {
			glRotated (90, 1, 0, 0);
		}
		else
		if (plane == PLANE_YZ_G18) {
			glRotated (-90, 0, 1, 0);
		}

	// the type of tool
		if (type == _RIGHT)  {	// diameter = 3 mm
		//1- right milling cutter
			// disc bottom: internal and external radius, number of sides, concentric zone
			gluDisk (temp, 0.0, R, 64, 1);
			// vertical cylinder axis Z on
			glTranslated (0, 0, -L);
			// cylinder
			gluCylinder(temp, R, R, L, 64, 1);
			// the top disc
			gluDisk (temp, 0.0, R, 64, 1);
		}
		else
		if (type == _HEMI) {	// diameter = 3 mm
		//2- milling cutter hemispherical
			// vertical cylinder axis Z on
			glTranslated (0, 0, -R);
			// lower sphere: radius, number of sides around Z, number of section along Z
			gluSphere (temp, R, 24, 12 );
			// vertical cylinder axis Z on
			glTranslated (0, 0, -L);
			// cylinder
			gluCylinder(temp, R, R, L, 64, 1);
			// the top disc
			gluDisk (temp, 0.0, R, 64, 1);
		}
		else
		if (type == _SHARP)	 {
		//3- sharp milling cutter
			glTranslated (0, 0, -H);
			// lower cone , radius base, radius top, length,  number of sides, number of section
			gluCylinder (temp, R, 0, H, 64, 1);
			// vertical cylinder axis Z on
			glTranslated (0, 0, -L);
			// cylinder
			gluCylinder(temp, R, R, L, 64, 1);
			// the top disc
			gluDisk (temp, 0.0, R, 64, 1);
		}
		else
		if (type == _SHARP_SHORT)	 {
		//3- sharp milling cutter
			H /= 2.0;  R /= 2.0;
			glTranslated (0, 0, -H);
			// lower cone , radius base, radius top, length,  number of sides, number of section
			gluCylinder (temp, R, 0, H, 64, 1);
			// vertical cylinder axis Z on
			glTranslated (0, 0, -L);
			// cylinder
			//gluCylinder(temp, R, R, L, 64, 1);
			// the top disc
			//gluDisk (temp, 0.0, R, 64, 1);
		}
		else
		if (type == _MINI) {	// diameter = 1 mm
		// lower sphere: radius, number of sides around Z, number of section along Z
			gluSphere (temp, R/3, 24, 12 );
		}
		// for the light reflection
		gluQuadricOrientation(temp, GLU_INSIDE);
	}
	glPopMatrix();
	gluDeleteQuadric(temp);
}
//------------------------------------------------------------------------------
