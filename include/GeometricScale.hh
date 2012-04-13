#ifndef _GEOMETRICSCALE_H_
#define _GEOMETRICSCALE_H_

#include <QtGui/QImage>

typedef enum GEOMETRIC_SCALE_METHOD
{
    NEAREST_NEIGHBOR,
    BILINEAR
} InterpolationMethod;

class GeometricScale
{
public:
    GeometricScale() {};
    virtual ~GeometricScale() {};
    static QImage convert(QImage *pic, double sx, double sy, InterpolationMethod m);
};

#endif /* _GEOMETRICSCALE_H_ */
