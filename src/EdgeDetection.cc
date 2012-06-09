#include "AlgebraicOp.hh"
#include "Erosion.hh"
#include "EdgeDetection.hh"

#define size _MX_size

QImage EdgeDetection::convert(QImage *pic)
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

    QImage *tmp = new QImage(Erosion::convert(pic, kernel));
    QImage res = AlgebraicOp::operate(*pic, *tmp, '-');

    delete tmp;

    return res;
}
