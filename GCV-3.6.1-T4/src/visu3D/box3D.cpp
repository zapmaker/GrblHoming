/***************************************************************
 * Name:    Box3D.cpp
 * Purpose:
 * Author:    LETARTARE
 * Created:   2014-20-06
 * Copyright: LETARTARE
 * License:   GPL
 **************************************************************/

#include "box3D.h"
#include <QtOpenGL>

Box3D::Box3D(const QVector3D p1, const QVector3D p2, bool mm1, QColor c)
		: pmin(p1), pmax(p2),
		  mm(mm1), color(c)

{
}

void Box3D::setColor(QColor c)
{
    color = c ;
}

void Box3D::setMm (bool bm)
{
  mm = bm;
}

void Box3D::setDim (QVector3D p1, QVector3D p2)
{
   pmin = p1; pmax = p2;
}


void Box3D::gdraw3D() const
{
  glLineWidth(1);
  glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());

  double p1x = pmin.x() , p1y = pmin.y() , p1z = pmin.z() ,
         p2x = pmax.x() , p2y = pmax.y(), p2z = pmax.z() ;
  /// establishes the pattern that the lines will use for drawing
  glLineStipple(1, 0x48FF);
  glEnable(GL_LINE_STIPPLE);

    glBegin(GL_LINE_STRIP);
      glVertex3d(p1x, p1y, p1z);
      glVertex3d(p1x, p2y, p1z);
      glVertex3d(p2x, p2y, p1z);
      glVertex3d(p2x, p1y, p1z);
      glVertex3d(p1x, p1y, p1z);
      glVertex3d(p1x, p1y, p2z);
      glVertex3d(p1x, p2y, p2z);
      glVertex3d(p2x, p2y, p2z);
      glVertex3d(p2x, p1y, p2z);
      glVertex3d(p1x, p1y, p2z);
    glEnd();

    glBegin(GL_LINES);
      glVertex3d(p1x, p2y, p1z);
      glVertex3d(p1x, p2y, p2z);
      glVertex3d(p2x, p2y, p1z);
      glVertex3d(p2x, p2y, p2z);
      glVertex3d(p2x, p1y, p1z);
      glVertex3d(p2x, p1y, p2z);
    glEnd();
  glDisable(GL_LINE_STIPPLE);
}

