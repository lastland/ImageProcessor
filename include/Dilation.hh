#ifndef _DILATION_H_
#define _DILATION_H_

#include "MatrixDialog.hh"
#include <QtGui/QImage>
#include <QtGui/QColor>

class Dilation
{
public:
    static QImage convert(QImage *pic, Matrix kernel);
private:
    static QRgb getMaxFromKernelBin(QImage *pic, int x, int y, Matrix kernel);
    static QRgb getMaxFromKernelGray(QImage *pic, int x, int y, Matrix kernel);
};

#endif /* _DILATION_H_ */
