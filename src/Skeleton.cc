#include <QtGui/QColor>
#include "AlgebraicOp.hh"
#include "Utility.hh"
#include "Skeleton.hh"

#define size _MX_size

QImage Skeleton::convert(QImage *pic)
{
    Matrix kernel;
    
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            kernel.value[i][j] = 0;
    
    kernel.value[size / 2][size / 2] = 1;
    kernel.value[size / 2 - 1][size / 2] = 1;
    kernel.value[size / 2][size / 2 - 1] = 1;
    kernel.value[size / 2 + 1][size / 2] = 1;
    kernel.value[size / 2][size / 2 + 1] = 1;
    
    QImage *img = new QImage(*pic);
    QImage *ske = new QImage(*pic);
    QImage *tmp1 = NULL, *tmp2 = NULL;
    QImage *ero = NULL;

    ske->fill(QColor(0, 0, 0).rgb());

    do
    {
        delete tmp1;
        delete tmp2;
        ero = new QImage(Erosion::convert(img, kernel));
        tmp1 = new QImage(Dilation::convert(ero, kernel));
        tmp2 = new QImage(AlgebraicOp::operate(*img, *tmp1, '-'));
        Utility::bitwise_or(ske, tmp2, ske);
        delete img;
        img = ero;
    }
    while (!Utility::isBlack(img));

    QImage res = QImage(*ske);

    delete ske;
    delete tmp1;
    delete tmp2;
    delete ero;

    return res;
}
