/***************************************************************
 * Name:  	  Arc3D.cpp
 * Purpose:
 * Author:    LETARTARE
 * Created:   2014-16-06
 * Copyright: LETARTARE
 * License:   GPL
 **************************************************************/
#include "Arc3D.h"
#include <QtOpenGL>
#include "definitions.h"       /// PLANE_XY_G17,...

Arc3D::Arc3D():
	plane(NO_PLANE),
	cw(true),
	pstart(), pend(), poffset(),
	nrevol(0)
{
	pcenter = pstart + poffset;
	radius = 0.0;
	astart = aend = 0.0;
	color = Qt::black;   /// noir
	linewidth = 1;
	speed = SPEED_DEFAULT;
	// no paths
	interpolated = false;
	 path.clear();
}

// arc for plane circle
Arc3D::Arc3D(float dia)
{
	radius = dia/2.0;
}

// arc for GCode  G2, G3
Arc3D::Arc3D(uint8_t p, bool dir,  QVector3D s, QVector3D e, QVector3D o, uint8_t r, bool h) :
	plane(p),
	cw(dir),
	pstart(s), pend(e),	poffset(o),
	nrevol(r),   // not used !!
	helix(h),
	pcenter(pstart + poffset),
	color(Qt::darkGreen),  /// green
	linewidth(1), speed(SPEED_DEFAULT)
{
	// no paths
	interpolated = false;
	path.clear();
//diag("GArc start	==> sx, sy, sz = %f, %f, %f", pstart.x(), pstart.y(), pstart.z());
//diag("GArc end	  	==> ex, ey, ez = %f, %f, %f", pend.x(), pend.y(), pend.z());
//diag("GArc offset	==> lx, ly, lz = %f, %f, %f", poffset.x(), poffset.y(), poffset.z());
//diag("GArc center	==> cx, cy, cz = %f, %f, %f", pcenter.x(), pcenter.y(), pcenter.z());
	/// plane selection
	double t2(0) , u2(0);   /// axes ?
//diag("Arc plane = %d", plane);
	switch (plane) {
		case PLANE_XY_G17 :  /// XY  G17
			pcenter.setZ(pstart.z()) ;
            t2 = qPow(pstart.x() - pcenter.x(), 2.0) ;
	//diag("sx , cx = %f, %f", pstart.x(), pcenter.x());
            u2 = qPow(pstart.y() - pcenter.y() , 2.0) ;
   // diag("sy , cy = %f, %f", pstart.y(), pcenter.y());
  //  diag("XY : t2 , u2 = %f, %f" , t2, u2);
            // angles
            astart = qAtan2(pstart.y()- pcenter.y(), pstart.x()- pcenter.x() );
            aend = qAtan2(pend.y()- pcenter.y(), pend.x()- pcenter.x() );
 //  diag("as , ae = %f, %f", astart, aend);
		break;
		case PLANE_ZX_G19 :  /// ZX  G18
			pcenter.setY(pstart.y()) ;
			t2 = qPow(pstart.x() - pcenter.x(), 2.0) ;
            u2 = qPow(pstart.z() - pcenter.z(), 2.0) ;
  //  diag("XZ : t2 , u2 = %f, %f" , t2, u2);
            //
            astart = qAtan2(pstart.z()- pcenter.z(), pstart.x()- pcenter.x() );
            aend = qAtan2(pend.z()- pcenter.z(), pend.x()- pcenter.x() );
			break;
		case PLANE_YZ_G18:  /// YZ  G19
			pcenter.setX(pstart.x());
			t2 = qPow(pstart.y() - pcenter.y(), 2.0) ;
            u2 = qPow(pstart.z() - pcenter.z(), 2.0) ;
   // diag("YZ : t2 , u2 = %f, %f" , t2, u2);
            //
            astart = qAtan2(pstart.z()- pcenter.z(), pstart.y()- pcenter.y() );
            aend = qAtan2(pend.z()- pcenter.z(), pend.y()- pcenter.y() );
			break;
		default :
			;
	}
	/// radius into plane
	radius  = qSqrt( t2 + u2 );
//diag("radius = %f", radius);
//diag("astart , aend = %f, %f", astart, aend);
}

Arc3D::~Arc3D()
{
	//dtor
}

void Arc3D::setColor(QColor c)
{
    color = c ;
}

void Arc3D::setLineWidth(int lw)
{
	if (lw > 0 && lw <= 10)
		linewidth = lw;
	else
		linewidth = 1;
}

void Arc3D::setSpeed (double f)
{
	if (f > SPEED_MIN && f <= SPEED_MAX)
		speed = f;
}

uint32_t Arc3D::interpolate(const double tol)
{
	if (interpolated)
		return path.size()-1;
    // no paths
    path.clear();
    // number of segments
    uint32_t seg ;
    if (radius) {
    	double as = astart
	       ,ae = aend
	          ,da;
	/// TO REWRITE !!
			//da = ae - as;  /// radians
		if (cw)
			da = -positive(as - ae);
		else
			da = positive(ae - as);
    /// <--
	// interpolation segments
		// calculating the start deflection in radians
		double defle = radius*(1-qCos(da/=2));
		// accumulates the number of divisions
		seg = 1;
		// calculate the deflection for fle <= tol
		if (defle > tol) {
			do {
				defle = radius*(1-qCos(da/=2));
				seg++;
			} while (defle > tol);

			seg = 1 << seg ;
			// with helix
			double dx(0), dy(0), dz(0);
			QVector3D pdh(0, 0, 0);
			if (helix) {
				switch (plane) {
					case PLANE_XY_G17:
						dz = (pend.z()-pstart.z())/(1.0*seg);
						pdh.setZ(dz);
						break;
					case PLANE_ZX_G19:
						dy = (pend.y()-pstart.y())/(1.0*seg);
						pdh.setY(dy);
						break;
					case PLANE_YZ_G18:
						dx = (pend.x()-pstart.x())/(1.0*seg);
						pdh.setX(dx);
						break;
				}
			}
			// generate segments interpolation from 'astart'
			double teta = astart;
			QVector3D p ;
			uint32_t npi = 0;
			// 'path' contains the end points of the vectors
			do {
				p = pointArc(teta);
				if (helix) {
					p += npi* pdh;
				}
			    path.append(p);
				teta += da;
			    npi++;
			} while (npi <= seg) ;

			interpolated = true;
		}
		else {
			seg = 1;
			path.append(pstart);
			path.append(pend);
		}
    }
    else {
		seg = 0;
    	path.append(pcenter);
    }
//diag("seg  : %d", seg);
	return seg ;
}

/// FOR TESTING ... it's correct
uint32_t Arc3D::interpolateS(const double tol, QList<QVector3D>& path1)
{
	if (interpolated)
		return path.size()-1;
    // no paths
    path.clear();
//diag("pstart = %f/%f/%f", pstart.x(), pstart.y(), pstart.z() );
//diag("pend = %f/%f/%f", pend.x(), pend.y(), pend.z() );
    // number of segments
    uint32_t seg ;
    if (radius) {
    	double as = astart
			  ,ae = aend
	          ,da;
	/// TO REWRITE !!
			// radians
		if (cw)
			da = -positive(as - ae);
		else
			da = positive(ae - as);
    /// <--
//diag("as , ae , cw = %f, %f, %s ", astart, aend, cw==0 ? "horaire" : "anti");
	// interpolation segments
	/// -> an another way to ...
		/// radians
		double dda =  2*qAcos(1- (tol/radius));
        seg = qRound(qAbs(da/dda)+ 0.5);
//diag("tol, radius, dda, seg  : %f, %f, %f, %d", tol, radius, dda, seg);
	/// <--
		// new increment dda
         dda = da / double(seg);
//diag("dda : %f", dda);
		// generate segments
		if (seg > 0 ) {
			// with helix ?
			double dx(0), dy(0), dz(0);
			QVector3D pdh(0, 0, 0);
			if (helix) {
				switch (plane) {
					case PLANE_XY_G17:
						dz = (pend.z()-pstart.z())/(1.0*seg);
						pdh.setZ(dz);
						break;
					case PLANE_ZX_G19:
						dy = (pend.y()-pstart.y())/(1.0*seg);
						pdh.setY(dy);
						break;
					case PLANE_YZ_G18:
						dx = (pend.x()-pstart.x())/(1.0*seg);
						pdh.setX(dx);
						break;
				}
			}
			// generate segments interpolation from 'astart'
			double teta = astart;
			QVector3D p ;
			uint32_t npi = 0;
			do {
				p = pointArc(teta);
				if (helix) {
					p += npi*pdh;
				}
			    path.append(p);
				teta += dda;
			    npi++;
			} while (npi <= seg) ;
			// 'path' contains the end points of the vectors
			interpolated = true;
		}
		else {  /// one segment
			seg = 1;
			path.append(pstart);
			path.append(pend);
		}
    }
    else {
		seg = 0;
    	path.append(pcenter);
    }

    path1 = path;

	return seg ;
}

// arc point from 'a' radian
QVector3D  Arc3D::pointArc ( const double a )
{
    double teta = normal(a);
    double dx(0), dy(0), dz(0);
    switch (plane) {
		case PLANE_XY_G17 :	/// XY
			dx = radius*qCos(teta) ;
			dy = radius*qSin(teta) ;
			dz = 0;
			break;
		case PLANE_ZX_G19 :	/// ZX
			dx = radius*qCos(teta) ;
			dy = 0;
			dz = radius*qSin(teta) ;
			break;
		case PLANE_YZ_G18 :	/// YZ
			dx = 0;
			dy = radius*qSin(teta) ;
			dz = radius*qCos(teta) ;
			break;
    }

    QVector3D P(pcenter.x() + dx, pcenter.y() + dy, pcenter.z() + dz  );
    return P;
}

void Arc3D::gdraw3D() const
{
	if (path.size() == 0)
        return;

    double psx = path.at(0).x()
		  ,psy = path.at(0).y()
		  ,psz = path.at(0).z() ;
	double  pex , pey, pez;

	glLineWidth(linewidth);
    glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
    glBegin(GL_LINE_STRIP);
		foreach (QVector3D p, path) {
			pex = p.x(); pey = p.y(); pez = p.z();
			glVertex3d(psx, psy, psz);
			glVertex3d(pex, pey, pez);
			psx = pex; psy = pey; psz = pez;
		}
    glEnd();
}

void Arc3D::MinMax(QVector3D& pmin, QVector3D& pmax)
{
	if (path.size() == 0)
        return;
    if (!interpolated)
		return;

	double  x , y, z;
	foreach (QVector3D p, path) {
		x = p.x(); y = p.y(); z = p.z();
		if (x > pmax.x()) pmax.setX(x);
		if (y > pmax.y()) pmax.setY(y);
		if (z > pmax.z()) pmax.setZ(z);

		if (x < pmin.x()) pmin.setX(x);
		if (y < pmin.y()) pmin.setY(y);
		if (z < pmin.z()) pmin.setZ(z);
	}
}

///-----------------------------------------------------------------------------
/// To VERIFY !!
///-----------------------------------------------------------------------------
// normalizes the value of the angle in [0..2*PI[
double Arc3D::positive (const double  VA)
{
    double V = VA;
// if < 0.0
	while (V <= 0.0)	//  0 -> 2*PI, (..2*PI] ) -2*k*PI -> 0  ( [0.. )
        V += 2*M_PI;
// if > 2*PI
 	while (V > 2*M_PI)  //  2*PI -> 2*PI  ( ..2*PI] )
        V -= 2*M_PI;
    return V;
}
///-----------------------------------------------------------------------------
/// To VERIFY  !!
///-----------------------------------------------------------------------------
// normalizes the value of the angle in [-PI..PI]
double Arc3D::normal ( const double  VA )
{
    double V = VA;
// if < -PI
    while (V < - M_PI)   // [-PI..
        V += 2*M_PI;
// if >= +PI
    while (V > M_PI)    // and -> ..PI]
        V -= 2*M_PI;
    return V;
}

// radians  => degrees
double Arc3D::deg (double a, emode m)
{
    if (m == _NORM )
        a = normal(a);
    else
        a = positive(a);

    return a *= (180.0/M_PI);
}

// degrees => radians
double Arc3D::rad(double a /*, emode m*/)
{
    a /= (180.0/M_PI);
    /*
    if (m == _NORM )
        a = normal(a);
    else
        a = positive(a);
    */
    return a ;
}
