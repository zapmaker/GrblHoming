#ifndef POSITEM_H
#define POSITEM_H
#include <QMetaType>
//#include "stdio.h"
#include "definitions.h"

class PosItem
{
public:
    PosItem()
        : x(0), y(0), i(0), j(0),
            arc(false), cw(false), mm(true), index(0) {}
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
    void toMm();
    void toInches();

public:
    double x;
    double y;
    double i;
    double j;
    bool arc;
    bool cw;
    bool mm;
    int index;
};

Q_DECLARE_METATYPE ( PosItem )

#endif // POSITEM_H
