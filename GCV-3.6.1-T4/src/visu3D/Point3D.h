/***************************************************************
 * Name:    Point3D.cpp
 * Purpose:
 * Author:    LETARTARE
 * Created:   2014-16-06
 * Copyright: LETARTARE
 * License:   GPL
 **************************************************************/

#ifndef POINT3D_H
#define POINT3D_H

#include <QtGui>


class Point3D
{
	public:
		Point3D();

		Point3D(const QColor c, const QVector3D s) ;

		virtual ~Point3D();

		void gdraw3D() const;

		void setColor (QColor);

		void MinMax(QVector3D&, QVector3D&);

	private:

		const QVector3D p ;
		QColor color;
		bool mm;
};

#endif // POINT3D_H
