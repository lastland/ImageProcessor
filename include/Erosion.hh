#ifndef _EROSION_H_
#define _EROSION_H_

#include "MatrixDialog.hh"
#include <QtGui/QImage>
#include <QtGui/QColor>

class Erosion
{
public:
    static QImage convert(QImage *pic, Matrix kernel);
private:
    static QRgb getMinFromKernel(QImage *pic, int x, int y, Matrix kernel);
};

#endif /* _EROSION_H_ */
