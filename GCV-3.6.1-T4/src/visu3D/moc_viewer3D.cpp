/****************************************************************************
** Meta object code from reading C++ file 'viewer3D.h'
**
** Created: Tue 15. Jul 17:43:05 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "viewer3D.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'viewer3D.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Viewer[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      38,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,
      31,   29,    7,    7, 0x05,
      64,    7,    7,    7, 0x05,
      85,    7,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
     105,    7,    7,    7, 0x0a,
     117,    7,    7,    7, 0x0a,
     132,    7,    7,    7, 0x0a,
     146,    7,    7,    7, 0x0a,
     160,    7,    7,    7, 0x0a,
     175,    7,    7,    7, 0x0a,
     188,    7,    7,    7, 0x0a,
     204,    7,    7,    7, 0x0a,
     218,    7,    7,    7, 0x0a,
     227,    7,    7,    7, 0x0a,
     259,  252,    7,    7, 0x0a,
     291,  287,    7,    7, 0x2a,
     315,    7,    7,    7, 0x0a,
     329,    7,    7,    7, 0x2a,
     339,    7,    7,    7, 0x0a,
     353,    7,    7,    7, 0x2a,
     363,    7,    7,    7, 0x0a,
     375,    7,    7,    7, 0x2a,
     383,    7,    7,    7, 0x0a,
     399,    7,    7,    7, 0x0a,
     414,    7,    7,    7, 0x0a,
     424,    7,    7,    7, 0x0a,
     434,    7,    7,    7, 0x0a,
     450,    7,    7,    7, 0x0a,
     470,    7,    7,    7, 0x0a,
     495,    7,    7,    7, 0x0a,
     509,    7,    7,    7, 0x0a,
     531,  526,  520,    7, 0x0a,
     551,    7,    7,    7, 0x0a,
     560,    7,    7,    7, 0x0a,
     571,    7,    7,    7, 0x0a,
     582,    7,    7,    7, 0x0a,
     594,    7,    7,    7, 0x0a,
     606,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Viewer[] = {
    "Viewer\0\0updateLCD(QVector3D)\0,\0"
    "setActiveLineVisuGcode(int,bool)\0"
    "setPauseVisual(bool)\0setLineNum(QString)\0"
    "set3DView()\0setFrontView()\0setBackView()\0"
    "setLeftView()\0setRightView()\0setTopView()\0"
    "setBottomView()\0setVectorUp()\0Help3D()\0"
    "setItems(QList<PosItem>)\0xyz,nl\0"
    "setLivePoint(QVector3D,int)\0xyz\0"
    "setLivePoint(QVector3D)\0setTool(bool)\0"
    "setTool()\0setBbox(bool)\0setBbox()\0"
    "setG0(bool)\0setG0()\0setVisual(bool)\0"
    "setPause(bool)\0setPrev()\0setNext()\0"
    "setVisualAuto()\0setNumLine(QString)\0"
    "setTotalNumLine(QString)\0runCode(bool)\0"
    "drawItem()\0float\0nl,f\0timeItem(int,float)\0"
    "noTool()\0miniTool()\0hemiTool()\0"
    "rightTool()\0sharpTool()\0finish()\0"
};

const QMetaObject Viewer::staticMetaObject = {
    { &QGLViewer::staticMetaObject, qt_meta_stringdata_Viewer,
      qt_meta_data_Viewer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Viewer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Viewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Viewer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Viewer))
        return static_cast<void*>(const_cast< Viewer*>(this));
    return QGLViewer::qt_metacast(_clname);
}

int Viewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLViewer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateLCD((*reinterpret_cast< QVector3D(*)>(_a[1]))); break;
        case 1: setActiveLineVisuGcode((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: setPauseVisual((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: setLineNum((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: set3DView(); break;
        case 5: setFrontView(); break;
        case 6: setBackView(); break;
        case 7: setLeftView(); break;
        case 8: setRightView(); break;
        case 9: setTopView(); break;
        case 10: setBottomView(); break;
        case 11: setVectorUp(); break;
        case 12: Help3D(); break;
        case 13: setItems((*reinterpret_cast< QList<PosItem>(*)>(_a[1]))); break;
        case 14: setLivePoint((*reinterpret_cast< QVector3D(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 15: setLivePoint((*reinterpret_cast< QVector3D(*)>(_a[1]))); break;
        case 16: setTool((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: setTool(); break;
        case 18: setBbox((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: setBbox(); break;
        case 20: setG0((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: setG0(); break;
        case 22: setVisual((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: setPause((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: setPrev(); break;
        case 25: setNext(); break;
        case 26: setVisualAuto(); break;
        case 27: setNumLine((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 28: setTotalNumLine((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 29: runCode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 30: drawItem(); break;
        case 31: { float _r = timeItem((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 32: noTool(); break;
        case 33: miniTool(); break;
        case 34: hemiTool(); break;
        case 35: rightTool(); break;
        case 36: sharpTool(); break;
        case 37: finish(); break;
        default: ;
        }
        _id -= 38;
    }
    return _id;
}

// SIGNAL 0
void Viewer::updateLCD(QVector3D _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Viewer::setActiveLineVisuGcode(int _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Viewer::setPauseVisual(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Viewer::setLineNum(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
