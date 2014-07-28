/***************************************************************
 * Name:    viewer3D.cpp
 * Purpose:
 * Author:    LETARTARE
 * Created:   2014-20-06
 * Copyright: LETARTARE
 * License:   GPL
 **************************************************************/

#include "viewer3D.h"
#include <math.h>
#include "point3D.h"
#include "line3D.h"
#include "arc3d.h"
#include "box3D.h"
#include "version.h"

// Constructor must call the base class constructor.
Viewer::Viewer(QWidget *parent1)
	: QGLViewer(parent1),  parent(parent1),
	radius(100.0), tol(0.005), // mm
	plane(PLANE_XY_G17),
	withtool(true), withbbox(true), withg0(true), created(false), first(true),
	vmax(10000),   // mm  -> 10 m
	vecBanned(vmax, vmax, vmax)
{
	restoreStateFromFile();
}

void Viewer::init()
{
	/// clear yellow
	setBackgroundColor(QColor(244, 237, 187));
	setForegroundColor(Qt::black);
	setSceneRadius(radius);
	/// front view
	setFrontView() ;
	/// create one tool
	Tool = Tools3D( 0, QVector3D() );
	///
	visu = false;
	pause = true;
	firstauto = true;
	runcode = false;
	npoint = -1;
	linecodeText = linecodeTextmax = 0;
	posPath = 0;
	pcurr = pprev = QVector3D();
	// timer animator
	repeatVisu = new QTimer(this);
	//setPeriod(250);
	connect(repeatVisu, SIGNAL(timeout()), this, SLOT(setVisualAuto()));
	// timer for points
	repeatPoint = new QTimer(this);
	connect(repeatPoint, SIGNAL(timeout()), this, SLOT(drawItem()));
}

/// called by 'MainWindow::preProcessFile(...)' with 'emit setItems(posList)'
void Viewer::setItems(QList<PosItem> itemsRcvd)
{
	// all items
    items = itemsRcvd ;
    foreach(PosItem item, items) {
		mm = item.mm ;
	}
	if (!mm) {
		vmax /= MM_IN_AN_INCH;
		radius /= MM_IN_AN_INCH;
		setSceneRadius(radius);
		vecBanned /= MM_IN_AN_INCH;
	}
    // create all
	gcreateScene();
	gcreateBbox();
	/// z + 10 mm
	float dz = 10;
	if (!mm)
		dz /= MM_IN_AN_INCH;
	pprev = pcurr = QVector3D(0, 0, pmax.z()+ dz);
	Tool.setUnit(mm);
	Tool.setPos(pcurr);
	gcreateTool();
    //
    setTextIsEnabled(true);
    first = true;
    itemrec  = true;
}
/// main routine
void Viewer::draw()
{
	if (itemrec)  {
        // Scene
		glCallList(_LSCENE);
        // Bounding box
        if (withbbox)  {
			glCallList(_LBBOX);
        }
        // dimensions text bounding box
        drawDimBbox();
        // Tool
        if (withtool) {
			glCallList(_LTOOL);
        }
		// define max and min
		setSceneBoundingBox (pvmin, pvmax);
		if (first) {
			set3DView();
			first = false;
		}
	}
}

void Viewer::drawDimBbox()
{
	glDisable(GL_LIGHTING);
	color= Qt::red;
	glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
	QString unit;
	QVector3D bpmin(pmin), bpmax(pmax);
	uint8_t n;
	if (mm) {
		unit = " mm"; n = 3;
	}
	else  {
		unit = " in"; n = 4;
	}

	drawText(10, height()-10 , "BoxMin : " + QString().setNum(bpmin.x(), 'f', n) + "/"
							   + QString().setNum(bpmin.y(), 'f', n) + "/"
							   + QString().setNum(bpmin.z(), 'f', n)  + unit
			);
	drawText(10, height()-25, "BoxMax : " + QString().setNum(bpmax.x(), 'f', n) + "/"
							   + QString().setNum(bpmax.y(), 'f', n) + "/"
							   + QString().setNum(bpmax.z(), 'f', n) + unit
			);
}

void Viewer::gcreateScene(int nl)
{
	glNewList(_LSCENE, GL_COMPILE) ;
		Scene(nl);
	glEndList();
}

void Viewer::gcreateBbox()
{
	glNewList(_LBBOX, GL_COMPILE) ;
	/// bounding box of items
		Box3D box(pmin, pmax, mm, Qt::red);
		box.gdraw3D();
	glEndList();
}

void Viewer::gcreateTool()
{
	glNewList(_LTOOL, GL_COMPILE) ;
		Tool.setPlane(plane);
		Tool.gdraw3D();
	glEndList();
}

// slot called by 'ui->doubleSpinBoxTol::valueChanged(double)'
void Viewer::setTolerance(double t)
{
	if (t != tol)  {
		tol = t;
		if (created) {
			gcreateScene();
			update();
		}
	}
//diag("viewer::tol %.3f", tol);
}

// slot called by 'MainWindow::::setSpeedToLine(QList<double>)'
void Viewer::setSpeedToLine(QList<double> stl)
{
	speedToLine = stl ;
}

// called for Gcode line valid
void Viewer::Scene(int nlColor){
    //
    if (items.size() == 0)
        return;
    // point last
	QVector3D plast(items.at(0).x, items.at(0).y, items.at(0).z);
	// min and max values
	pmin = QVector3D(vmax, vmax, vmax);
    pmax = QVector3D(-vmax,-vmax, -vmax);;

    uint8_t plane(NO_PLANE);

	Arc3D arc;
	Line3D line;
    QVector3D pend, poffset, point;

	/// no path interpolated
	posPath = 0;
	pathComplete.clear();
	pointToLine.clear();
	speedByLineValid.clear();
	segToLineValid.clear();
	// speed
	speed = prevspeed = 0; // SPEED_DEFAUL ?
	bool element;
	uint32_t seg = 0;

	/// all items
    foreach (PosItem item, items) {
    	pathItem.clear();
    	// unit
    	mm = item.mm;
//diag("Scene::mm = %s", mm==true?"true":"false");
    	pend = QVector3D(item.x, item.y, item.z);
		element = item.g == 0 || item.g == 1 || item.g == 2 || item.g == 3 ;
		/// Fxxxx
		if (!element) {
			if (item.speed > 0) {
				speed = item.speed;
				/// QMap<int index, float speed>
				speedByLineValid.insert(item.index, speed);
			}
			else
			if (prevspeed == 0)
				speed = 0;
			else
				speed = prevspeed;

			seg = 0;
		}
		/// Element
		else {
			if (item.speed > 0)
				speed = item.speed;
			else
				speed = prevspeed;
		/// line G0  fast
			if (item.g == 0)  {
				seg = 1;
				if (withg0) {
					/// one line
					line = Line3D(plast, pend);
					if (item.index == nlColor) {
						line.setColor(Qt::red);
						line.setLineWidth(4);
					}
					else  {
						line.setColor(Qt::magenta);
						line.setLineWidth(1);
					}
					/// point min and max
					line.MinMax(pmin, pmax);
					// speed  max ??
					line.setSpeed(speed);
					/// fill list
					line.gdraw3D() ;
				}
			}
			else
		/// line  G1  work
			if (item.g == 1) {
				seg = 1;
				/// one line
				line = Line3D(plast, pend) ;
				if (item.index == nlColor) {
					line.setColor(Qt::red);
					line.setLineWidth(4);
				}
				else  {
					line.setColor(Qt::darkBlue);
					line.setLineWidth(1);
				}
				/// point min and max
				line.MinMax(pmin, pmax);
				// speed
				line.setSpeed(speed);
				/// fill list
				line.gdraw3D() ;
			}
			else
		/// arcs, helix :  G2, G3  work
			if (item.g == 2 || item.g == 3)  // G2, G3
			{
				poffset = QVector3D(item.i, item.j, item.k);
				/// one arc
				plane = item.plane;
				arc = Arc3D(plane, item.cw, plast, pend, poffset, 2, item.helix);
				/// interpolate with tolerance
				//arc.interpolate(tol);
				seg = arc.interpolateS(tol, pathItem);
				/// point min and max gcodeText.append(line);
				arc.MinMax(pmin, pmax) ;
				arc.setLineWidth(1);
				if (item.index == nlColor)   {
					arc.setColor(Qt::red);
					arc.setLineWidth(4);
				}
				/// speed
				arc.setSpeed(speed);
				/// fill list
				arc.gdraw3D();
			}
		/// another ...
			else {
			//	spline G5, G5.1, G5.2  ...
			}
			/// path item
			pathItem.append(pend);
			plast = pend;
			/// fill list points
			foreach(QVector3D p, pathItem) 	{
				/// QList<int line>
				pointToLine.append(item.index);
				/// QList<QVector3D Point>
				pathComplete.append(p);
			}
		}
//diag(" item.index %d -> seg = %d", item.index, seg);
		/// QMap<int index, float speed>
		speedByLineValid.insert(item.index, speed);
		/// QMap<int index, int seg>
		segToLineValid.insert(item.index, seg);
		prevspeed = speed ;
    }
    /// last number point [0..npointmax]
	npointmax = pathComplete.size()-1;
	/// for bounding box
    pvmin = qglviewer::Vec (pmin.x(), pmin.y(), pmin.z());
    pvmax = qglviewer::Vec (pmax.x(), pmax.y(), pmax.z());
    pvcenter = (pvmax - pvmin )/2.0;


    /// created scene
    created = true;
/*
int u = 0;
foreach (int seg , segToLineValid)
diag("%d -> seg : %d", u++, seg);
*/
}

void Viewer::Help3D()
{
	help();
}

QString Viewer::helpString() const
{
  QString text("<center>");
 // text += "<br><img src=\"img\gaia2.jpg\">" ;
  text += "<h1>V i e w e r 3 D</h1>";
  text += tr("<h3>Version %1</h3>").arg("T4");
  text += tr("<code>by LETARTARE  %1</code>").arg("https://github.com/LETARTARE");
  text += tr("<br><br> for  <h2> %1</h2>").arg(GRBL_CONTROLLER_NAME_AND_VERSION );
  text += QString("<code>ZAPMAKER  %1</code>").arg("https://github.com/zapmaker/GrblHoming<br>");

  text += tr("<br>Displays the <b>Path</b> GCode using 'OpenGL'.") ;
  text += tr("<br><br><i>Move the camera using the mouse.</i>");

  text += "</center><br>";
  return text;
}

void Viewer::setFrontView()
{
	/// front view (-Z)
	camera()->setViewDirection(qglviewer::Vec(0, 0, -1));
    /// directs the scene vertically upwards
	camera()->setUpVector (qglviewer::Vec(0, 1, 0));
	// all items
	showEntireScene();
}
void Viewer::setBackView()
{
	/// front view (Z)
	camera()->setViewDirection(qglviewer::Vec(0, 0, 1));
    /// directs the scene vertically upwards
	camera()->setUpVector (qglviewer::Vec(0, 1, 0));
	// all items
	showEntireScene();
}

void Viewer::setLeftView()
{
	/// left view  (X)
	camera()->setViewDirection(qglviewer::Vec(1, 0, 0));
    /// directs the scene vertically upwards
	camera()->setUpVector (qglviewer::Vec(0, 1, 0));
	// all items
	showEntireScene();
}
void Viewer::setRightView()
{
	/// right view (-X)
	camera()->setViewDirection(qglviewer::Vec(-1, 0, 0));
    /// directs the scene vertically upwards
	camera()->setUpVector (qglviewer::Vec(0, 1, 0));
	// all items
	showEntireScene();
}
void Viewer::setTopView()
{
	/// top view (-Y)
	camera()->setViewDirection(qglviewer::Vec(0, -1, 0));
    /// sets the scene following the Z axis down
	camera()->setUpVector (qglviewer::Vec(0, 0, -1));
	// all items
	showEntireScene();
}
void Viewer::setBottomView()
{
	/// top view (Y)
	camera()->setViewDirection(qglviewer::Vec(0, 1, 0));
    /// sets the scene following the Z axis up
	camera()->setUpVector (qglviewer::Vec(0, 0, 1));
	// all items
	showEntireScene();
}
void Viewer::set3DView()
{
	/// 3D view  (-x, -Y, -Z)
	camera()->setViewDirection(qglviewer::Vec(-1, -1, -1));
    /// directs the scene vertically upwards
	//camera()->setUpVector (qglviewer::Vec(0, 1, 0 ));
	camera()->setUpVector (qglviewer::Vec(-2, 4, -3));
	// all items
	showEntireScene();
}
void Viewer::setVectorUp()
{
	/// directs the scene vertically upwards
	camera()->setUpVector (qglviewer::Vec(0, 1, 0));
	// all items
	showEntireScene();
}

/// T4
///  display a point
void Viewer::setLivePoint(QVector3D xyz, int nl)   /// + bool mm  , bool isLiveCP ?
{
	/// tool
	if (xyz != vecBanned) {
		pprev = pcurr;
//diag("setLivePoint::pprev = %0.2f/%.02f/%0.2f", pprev.x(), pprev.y(), pprev.z() );
		pcurr = xyz;
//diag("setLivePoint::pcurr = %0.2f/%0.2f/%0.2f", pcurr.x(), pcurr.y(), pcurr.z() );
		Tool.setPos(pcurr);
		gcreateTool();
		/// scene
		if (nl) {
			gcreateScene(nl);
		}
		else   {
			gcreateScene() ;
		}
		update();
	}
	// display colored line to 'visuGcode'
	emit setActiveLineVisuGcode(nl, true);
	// display xyz
	if (visu || posReqKind == POS_SYNC)
		emit updateLCD(pcurr);
}

void Viewer::setTotalNumLine(QString str)
{
	linecodeTextmax = str.toUInt();
}

///
double Viewer::getSpeed(int nl)
{
	double s(SPEED_FAST);
	if (!mm)
		s /= MM_IN_AN_INCH;
	if (nl >= 0 && nl <= linecodeTextmax )  {
		s = speedToLine.value(nl);
	}
	return s;
}

/// MainWindow::setActiveLineVisuGcode(int, bool)' ->  emit setNumLine(strline);
// receive a line number into  1..linecodeTextmax
void Viewer::setNumLine(QString strline)
{
	int nl = strline.toUInt();
	if (nl != linecodeText) {
		speed = getSpeed(nl);
		emit setSpeedGcode(speed);
//diag("nl %d -> speed %0.2f", nl, speed);
		linecodeText = nl;
		if (!runcode) {
			if (repeatPoint->isActive())  {
				repeatPoint->stop();
			}
			ptemp = getLastPoint(nl) ;
			if (ptemp != vecBanned)  {
				setLivePoint(ptemp, nl);	// item colored in red
			}
			else  {
				setLivePoint(pcurr);		// item colored normally
			}
			emit setSegments(getSeg(linecodeText));
		}
		else {
//diag("\n");
			if (pointToLine.contains(nl)) {
				// stop timer
				if (repeatPoint->isActive())
					repeatPoint->stop();
				npmax = pointToLine.count(nl) ;
//diag("nl : %d -> npmax = %d", nl, npmax);
				nfirstpoint = pointToLine.indexOf(nl);
				pointsItem  = pathComplete.mid( nfirstpoint, npmax);
				np = 0;
//diag("nl %d -> speed %0.2f", nl, speed);
				/// first item point
				ptemp = pointsItem.value(np);
				QVector3D pc;
				float length;
				int msec;
			// line
				if (npmax == 1) {
					pc = pcurr;
					// total length mm
					length =  (ptemp - pc).length();
					// mm/S
					speed = speed/60;
					// total duration
					msec = 1000*(length /speed);
//diag("line->nl %d -> length : %5.2f / speed %5.2f -> msec %d", nl, length, speed, msec);
					/// time mini for one segment = 200 mS
					float tmini = 200.0;
					npmax = msec/tmini;
//diag("npmax = %d", npmax);
					if (npmax > 1)  {
						/// remplir poinstItem  ; firstp = pcur + dp, lastp = ptemp
						pointsItem.clear();
						QVector3D dp = (ptemp - pc)/npmax;
						for (int u = 1; u <= npmax; u++) {
							ptemp = pc + u*dp ;
							pointsItem.append(ptemp);
//diag("line->ptemp = %0.2f/%0.2f/%0.2f", ptemp.x(), ptemp.y(), ptemp.z() );
						}
						// !! coefficient !!
						msec = tmini/5.0;
					}
					else
						npmax = 1;

					emit setSegments(npmax);
					/// repeat all msec
					repeatPoint->start(msec);
				}
			// arc
				else {
					pc = ptemp;
					ptemp = pointsItem.value(np+1);
//diag("pc = %0.2f/%0.2f/%0.2f", pc.x(), pc.y(), pc.z() );
//diag("ptemp = %0.2f/%0.2f/%0.2f", ptemp.x(), ptemp.y(), ptemp.z() );
					/// a segment length mm
					length =  (ptemp - pc).length();
					/// mm/S
					speed = speed/60;
					msec = 1000*(length /speed);
					/// coefficient !!!
					msec *= 1.5;
					//int msec = timeItem(npmax, speed);
//diag("arc->nl %d -> length : %5.2f / speed %5.2f -> msec %d", nl, length, speed, msec);
					emit setSegments(npmax);
					/// repeat all msec
					repeatPoint->start(msec);
				}
			}
		}
	}
}

void Viewer::drawItem()
{
	if (!runcode && repeatPoint->isActive() )  {
			repeatPoint->stop();
	}
	else
	if  (np < npmax) {
		pp = pointsItem.value(np);
		setLivePoint(pp, linecodeText);
		np++ ;
		if (np >= npmax) {
			repeatPoint->stop();
		}
	}
}

float Viewer::timeItem(int np, float speed)
{
	/// path length between two points
	float length =  np*(pcurr -pprev).length();
	// steps per mm  -> 1 step = 0.01 mm
	//int stepsPerMm = 100;
	//int steps = length * stepsPerMm;
	// 1200 mm per mn ->  20 mm per second -> 0.02 mm per mS
	float msec = length /speed;

	return msec;
}

// get last point from line number
QVector3D Viewer::getLastPoint(int nl)
{
	/// verify nl
	if (pointToLine.contains(nl)) {
		npoint = pointToLine.lastIndexOf(nl);
		ptemp = pathComplete.at(npoint);
	}
	else  {
		ptemp = vecBanned;
	}

	return ptemp;
}

// called by 'MainWindow::toVisual(valid)'
// works with line number
void Viewer::setVisual(bool valid)
{
	visu = valid;
	if (visu && !linecodeText) {
		npoint = -1 ;
		linecodeText = 1;
		ptemp = getLastPoint(linecodeText);
		setLivePoint(ptemp, linecodeText) ;
	}
}

// called by 'MainWindow::toPause(valid)'
void Viewer::setPause(bool valid)
{
	pause = valid;
	if (visu) {
		if (pause) {
			repeatVisu->stop();
		}
		else {
			repeatVisu->start(250);
		}
	}
}
// works with line number
void Viewer::setPrev()
{
	if (visu && pause) {
		if (linecodeText > 1) {
			linecodeText--;
		/// read  one vector
			ptemp = getLastPoint(linecodeText) ;
			emit setSpeedGcode(getSpeed(linecodeText)) ;
			emit setLineNum(QString::number(linecodeText));
			emit setSegments(getSeg(linecodeText));
			setLivePoint(ptemp, linecodeText);
		}
		else
		if (repeatVisu->isActive())  {
			repeatVisu->stop();
			first = true;
		}
	}
}
// works with line number
void Viewer::setNext()
{
	if (visu && pause) {
		if (linecodeText < linecodeTextmax) {
			linecodeText++;
			/// read  one vector
			ptemp = getLastPoint(linecodeText) ;
			emit setSpeedGcode(getSpeed(linecodeText)) ;
			emit setLineNum(QString::number(linecodeText)) ;
			emit setSegments(getSeg(linecodeText));
			setLivePoint(ptemp, linecodeText);
		}
		else
		if (repeatVisu->isActive())  {
			repeatVisu->stop();
			first = true;
		}
	}
}

uint32_t Viewer::getSeg(int nl)
{
	uint32_t seg(0);
	if (segToLineValid.contains(nl) )
		seg= segToLineValid.value(nl);

	return seg;
}

// called by Timer 'Viewer::repeat' all '250'  mS
// works with point number and line number
void Viewer::setVisualAuto()
{
	if (visu && !pause) {
		if (firstauto) {
			npoint = -1;
			firstauto = false;
		}
		if (npoint < npointmax) {
			npoint++;
			/// read  one vector
			ptemp = pathComplete.at(npoint) ;
			linecodeText = pointToLine.at(npoint);
			emit setSpeedGcode(getSpeed(linecodeText)) ;
			emit setLineNum(QString::number(linecodeText)) ;
			emit setSegments(getSeg(linecodeText));
			setLivePoint(ptemp, linecodeText);
		}
		else
		if (repeatVisu->isActive()) {
			repeatVisu->stop();
			first = true;
			firstauto = true;
			/// run visu -> pause visu
			emit setPauseVisual(true);
		}
	}
}

// called by 'MainWindow::begin()' : emit runCode(true);
// called by 'MainWindow::stop()' : emit runCode(false);
void Viewer::runCode(bool run, int posreqkind)
{
//diag("runCode : %s", run==true ? "true" : "false");
	runcode = run;
	posReqKind = posreqkind ;
	if (runcode && repeatVisu->isActive()) {
		repeatVisu->stop();
		firstauto = true;
	}
}

void Viewer::setPeriod(int p)
{
	if (p > 100 && p <= 1000)
		repeatVisu->setInterval(p) ;
}

void Viewer::noTool()
{
	withtool = false;
}

void Viewer::miniTool()
{
	Tool.setTool(Tools3D::_MINI);
	withtool = true;
	gcreateTool();
}

void Viewer::hemiTool()
{
	Tool.setTool(Tools3D::_HEMI);
	withtool = true;
	gcreateTool();
}

void Viewer::rightTool()
{
	Tool.setTool(Tools3D::_RIGHT);
	withtool = true;
	gcreateTool();
}

void Viewer::sharpTool()
{
	Tool.setTool(Tools3D::_SHARP);
	withtool = true;
	gcreateTool();
}

void Viewer::shortTool()
{
	Tool.setTool(Tools3D::_SHARP_SHORT);
	withtool = true;
	gcreateTool();
}

void Viewer::setTool(bool with)
{
	withtool = with;
	update();
}

void Viewer::setBbox(bool with)
{
	withbbox = with;
	update();
}

void Viewer::setG0(bool with)
{
	withg0 = with;
	if (created) {
		gcreateScene();
		update();
	}
}

///-----------------------------------------------------------------------------
