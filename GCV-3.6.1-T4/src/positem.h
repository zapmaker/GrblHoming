#ifndef POSITEM_H
#define POSITEM_H
#include <QMetaType>
#include <QtGui>

#include "stdint.h"
#include "definitions.h"

/// T4 uses z, k, p

class PosItem
{
public:
/// 1- visu XY
   /// constructor 2 axes
    PosItem(double x1, double y1)
        : x(x1), y(y1), i(0), j(0),
            arc(false), cw(false), mm(true), index(0) {}
    PosItem(double x1, double y1, double i1, double j1)
        : x(x1), y(y1), i(i1), j(j1),
            arc(false), cw(false), mm(true), index(0) {}
    PosItem(double x1, double y1, double i1, double j1, bool arc1, bool cw1, bool mm1, int index1)
        : x(x1), y(y1), i(i1), j(j1),
            arc(arc1), cw(cw1), mm(mm1), index(index1) {}

    void setCoords(double x1, double y1, double i1, double j1);
    void setCoords(double x1, double y1, bool mm);
    void expand(const PosItem& item);
    double width() { return qAbs(i - x); }
    double height() { return qAbs(j - y); }
    bool isNull() { return x == 0 && y == 0 && i == 0 && j == 0 && arc == false && cw == false && index == 0; }

/// 2- visu XYZ
    /// constructor 2, 3 axes
    PosItem()
        : x(0), y(0), z(0),
          i(0), j(0), k(0) ,
          p(0), arc(false), cw(true),
          mm(true), g(0),
          plane(PLANE_XY_G17), helix(false),
          index(0), feedrate(0)
    {}
    /// constructeur 3 axes
    PosItem(double x1, double y1, double z1)
        : x(x1), y(y1), z(z1), i(0), j(0), k(0), p(0),
            arc(false), cw(false), mm(true), g(0), plane(0), index() {}
    /// constructeur 3 axes
    PosItem(double x1, double y1, double z1, double i1, double j1, double k1)
        : x(x1), y(y1), z(z1), i(i1), j(j1), k(k1) ,
            arc(false), cw(false), mm(true), g(0), plane(0), index(0) {}
/// T4
    /// constructeur 3 axes  with real
    PosItem(double x1, double y1, double z1,
            double i1, double j1, double k1,
            int pr1, bool arc1, bool cw1,
            bool mm1, int g1,
            int pl, bool hel, int index1, double f
            )
        : x(x1), y(y1), z(z1),
          i(i1), j(j1), k(k1) ,
          p(pr1), arc(arc1), cw(cw1),
          mm(mm1), g(g1),
          plane(pl), helix(hel), index(index1) , feedrate(f) {}
    /// + line gcode
    PosItem(QString linecode,
            double x1, double y1, double z1,
            double i1, double j1, double k1,
            int pr1, bool arc1, bool cw1,
            bool mm1, int g1,
            int pl, bool hel , int index1, double f
            )
        : line(linecode),
          x(x1), y(y1), z(z1),
          i(i1), j(j1), k(k1) ,
          p(pr1), arc(arc1), cw(cw1),
          mm(mm1), g(g1),
          plane(pl), helix(hel), index(index1), feedrate(f) {}


    /// constructeur 3 axes with Vector
    PosItem(QVector3D xyz,
            QVector3D ijk,
            int pr1, bool arc1, bool cw1,
            bool mm1, int g1,
            int pl, bool hel,
            int index1, double f1, double s1
            )
        : x(xyz.x()), y(xyz.y()), z(xyz.z()),
          i(ijk.x()), j(ijk.y()), k(ijk.z()),
          p(pr1), arc(arc1), cw(cw1),
          mm(mm1), g(g1),
          plane(pl), helix(hel), index(index1) , feedrate (f1), speedspindle(s1) {}

    /// constructeur 3 axes with Vector + line gcode
    PosItem( QString linecode,
            QVector3D xyz,
            QVector3D ijk,
            int pr1, bool arc1, bool cw1,
            bool mm1, int g1,
            int pl, bool hel,
            int index1 , double f1, double s1
            )
        : line(linecode),
          x(xyz.x()), y(xyz.y()), z(xyz.z()),
          i(ijk.x()), j(ijk.y()), k(ijk.z()),
          p(pr1), arc(arc1), cw(cw1),
          mm(mm1), g(g1),
          plane(pl), helix(hel), index(index1) , feedrate(f1), speedspindle(s1) {}

    void setCoords(double x1, double y1, double z1, double i1, double j1, double k1);
    void setCoords(QVector3D xyz1, QVector3D ijk1);
    void setCoords(double x1, double y1, double z1, bool mm);

/// T4
    void toMm();
    void toInches();

public:
    QString line;
    double x, y, z;
    double i, j, k;

    int p;      // arc revolutions
    bool arc ;
    bool cw;
    bool mm;
    int g;     // in [0..3] for Gx
/// T4
    int plane;
    bool helix;
     // ligne GCode
    int index;
    double feedrate;
    double speedspindle ;
};

Q_DECLARE_METATYPE ( PosItem )

#endif // POSITEM_H
