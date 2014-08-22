/***************************************************************
 * Name:  	  Arc3D.h
 * Purpose:
 * Author:    LETARTARE
 * Created:   2014-16-06
 * Copyright: LETARTARE
 * License:   GPL
 **************************************************************/

#ifndef ARC3D_H
#define ARC3D_H

#include <QtGui>
#include <stdint.h>          /// uint8_t, ...

class Arc3D
{

	// mode = NORM -> all angles are in [-PI..+PI[
	// mode = POSI -> all angles are in  [0..2*PI]
	enum emode { _NORM, _POSI };

	public:
		Arc3D();
		// arc for plane circle
		Arc3D(float diameter);
        // arc for GCode  G2, G3
		Arc3D(uint8_t plane, bool dir, QVector3D pstart, QVector3D pend,
				QVector3D poffset, uint8_t revolutions, bool helix=false);

		virtual ~Arc3D();

		void gdraw3D() const;

		void setColor (QColor);

		void setLineWidth(int)  ;

		void setSpeed (double);

		uint32_t interpolateSeg(const double tol );

		uint32_t interpolateAng(const double tol, QList<QVector3D>& path1 );

		 void MinMax(QVector3D&, QVector3D&);

	private:
    ///fonctions
		QVector3D pointArc ( const double angle);
		// normalizes the value of the angle in [0..2*PI[
		double positive (const double  VA);
		// normalizes the value of the angle in [-PI..PI]
		double normal ( const double  VA );
		// radians -> degrees
		double deg (double a, emode m = _POSI);
		// degrees -> radians
		double rad(double a /*, emode m = _POSI*/);

    /// attributs

		/// plane selection XY (G17) = 0, ZX (G18) = 1, YZ (G19) = 2
		uint8_t plane;
		bool cw;                 // direction
		QVector3D pstart, pend;  // x, y, z
		QVector3D poffset;       // i, j, k
		uint8_t   nrevol;        // revolutions
		bool helix;				 // helix
		/// calculated
		QVector3D pcenter;       // center
		double radius;           // radius
		double astart, aend;	 // angles   (radians)
		// buffer path
		QList<QVector3D> path;
		bool interpolated;

		// The color with which this item should be displayed
		QColor color;
		int linewidth;
		double feedrate;
};


#endif // ARC_H
