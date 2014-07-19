#ifndef COORD3D_H
#define COORD3D_H

#include <QMetaType>
#include <QVector3D>

class Coord3D
{
public:
    Coord3D();
/// T4 animator
    Coord3D(QVector3D);
    bool operator==(const Coord3D& rhs);

public:
    float x;
    float y;
    float z;
    float fourth;
    bool stoppedZ;
    int sliderZIndex;
};

Q_DECLARE_METATYPE ( Coord3D )

#endif // COORD3D_H
