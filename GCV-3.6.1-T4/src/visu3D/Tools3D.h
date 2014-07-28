/***************************************************************
 * Name:    Tools3D.h
 * Purpose:
 * Author:    LETARTARE
 * Created:   2014-20-06
 * Copyright: LETARTARE
 * License:   GPL
 **************************************************************/

#ifndef TOOLS3D_H
#define TOOLS3D_H

#include <QtGui>
#include <QGLViewer/qglviewer.h>
#include <stdint.h>	// uint8_t ...

class Tools3D
{
	public:
		enum typeTool {_MINI=0, _RIGHT, _HEMI, _SHARP, _SHARP_SHORT};

		Tools3D();

		Tools3D(uint8_t plane, QVector3D s, typeTool type=_SHARP_SHORT);

		virtual ~Tools3D();

		void gdraw3D() const;

		void setColor (QColor);

		void setPlane(uint8_t);

		void setPos(QVector3D);
		void setPos(qglviewer::Vec);
		void setPos(double x, double y, double z);
		void setTool(typeTool);
		void setUnit(bool mm);

	private:

		uint8_t plane ;
		QVector3D start;
		typeTool type;
		QColor color;
		bool mm;
};

#endif // POINT3D_H
