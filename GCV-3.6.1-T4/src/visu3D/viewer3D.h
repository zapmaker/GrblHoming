/***************************************************************
 * Name:    viewer3D.h
 * Purpose:
 * Author:    LETARTARE
 * Created:   2014-20-06
 * Copyright: LETARTARE
 * License:   GPL
 **************************************************************/
#ifndef VIEWER3D_H
#define VIEWER3D_H

#include <QGLViewer/qglviewer.h>
/// T4
#include <QtOpenGL>
#include <QThread>
#include <stdint.h>
#include "Tools3D.h"

#include "positem.h"

class Viewer : public QGLViewer
{
	Q_OBJECT
public :
	enum glist {_LSCENE=1000, _LBBOX, _LTOOL};

	Viewer(QWidget *parent);
	virtual void init();

protected :

	virtual void draw();

	double getSpeed(int nl);
	uint32_t getSeg(int nl);

signals:
	void updateLCD(QVector3D);
	void setActiveLineVisuGcode(int, bool);
	void setPauseVisual(bool);
	void setLineNum(QString);
	void setSpeedGcode(double);
	void setSegments(int);

public Q_SLOTS:

	void set3DView();
	void setFrontView();
	void setBackView();
	void setLeftView();
	void setRightView();
	void setTopView();
	void setBottomView();
	void setVectorUp();

	void Help3D();

    void setItems(QList<PosItem>);

/// T4
    void setLivePoint(QVector3D xyz, int nl=0);
///<-
	void setTool(bool=false);
	void setBbox(bool=false);
	void setG0(bool=false);
/// animator
	void setVisual(bool);
	void setPause(bool);
	void setPrev() ;
	void setNext() ;
	void setVisualAuto();
	void setNumLine(QString);
	void setTotalNumLine(QString);
	void setSpeedToLine(QList<double>);
	void runCode(bool, int) ;

	void  drawItem() ;
	float  timeItem(int nl, float f) ;
	///
	void noTool() ;
	void miniTool();
	void hemiTool();
	void rightTool();
	void sharpTool();
	void shortTool();

	void setPeriod(int);
	void setTolerance(double);

private:

/// fonctions
	virtual QString helpString() const;
	/// create Gl list
	void gcreateScene(int=0);
	void gcreateTool() ;
	void gcreateBbox() ;
	// objets draw
	void Scene(int nlColor=0);
	/// bounding box
	void drawDimBbox();
	void MinMax(QVector3D);

	QVector3D getLastPoint(int) ;
	void getPoints(int nl) ;

/// attributs
	QWidget * parent;
	float radius ;
	//  tolerance
    double tol;
    bool mm;
    uint8_t plane;
	bool itemrec, withtool, withbbox, withg0, created, first;

    // scene size max
    uint16_t vmax ;
    // vectors
    QVector3D  vecBanned;
    QVector3D pmax, pmin, pcurr, pprev, ptemp, pp;
	qglviewer::Vec pvmax, pvmin, pvcenter;
	Tools3D Tool;
	// positions
	PosItem livePoint;
    QList<PosItem> items;

	int linecodeText, linecodeTextmax;

    // paths
    QList<QVector3D> pathItem, pointsItem;
    QList<QVector3D> pathComplete;
    QList<int>	pointToLine;
    QList<double> speedToLine;
    QMap<int, int> segToLineValid;
    QMap<int, float> speedByLineValid;

	/// line -> pathComplete
	int posPath ;
	// motor steps
	QList<QVector3D> stepsItem;
	QList<QVector3D> stepsComplete;

	QColor color;

	// animator
	bool visu, pause, runcode, firstauto;
	int npoint, npointmax, np, npmax,nfirstpoint, nlastpoint ;
	QTimer * repeatVisu;
	QTimer * repeatPoint;
    // from PosItem
	float speed, prevspeed ;  /// mm per mn
	// from grbl $$? depending on version  ?
//	uint16_t stepsPerMm  ;  /// steps per mm
	// mode request display
	int posReqKind ;
};
#endif
