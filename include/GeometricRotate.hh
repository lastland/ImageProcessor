#ifndef _GEOMETRICROTATE_H_
#define _GEOMETRICROTATE_H_

#include <QtGui/QImage>
#include "GeometricScale.hh"

class GeometricRotate
{
public:
    GeometricRotate() {};
    virtual ~GeometricRotate() {};
    static QImage convert(QImage *pic, double angle, InterpolationMethod m);
};

#endif /* _GEOMETRICROTATE_H_ */
