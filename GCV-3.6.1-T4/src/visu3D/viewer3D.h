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
//#include <QThread>
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

	double getFeedRate(int nl);
	double getSpeedSpindle(int nl);
	uint32_t getSeg(int nl);

signals:
	void updateLCD(QVector3D);
	void setActiveLineVisuGcode(int, bool);
	void setPauseVisual(bool);
	void setLineNum(QString);
	void setFeedRateGcode(double);
	void setSpeedSpindleGcode(double);
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
    void setLivePoint(QVector3D xyz, bool useMm=true, int nl=0);
    void setLiveRelPoint(QVector3D dxyz, int nl=0);
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
	void setFeedRateToLine(QList<double>);
	void setSpeedSpindleToLine(QList<double>);
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
    QVector3D  vecBanned, phome;
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
    QList<double> feedRateToLine;
    QList<double> speedSpindleToLine;
    QMap<int, int> segToLineValid;
    QMap<int, float> feedRateByLineValid;
    QMap<int, float> speedSpindleByLineValid;

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
	float feedrate, prevfeedrate ;  // mm per mn
	float speedspindle, prevspeedspindle; 	// turn per minute
	// mode request display
	int posReqKind ;
};
#endif
