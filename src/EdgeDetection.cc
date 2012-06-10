#include "AlgebraicOp.hh"
#include "Erosion.hh"
#include "Kernel.hh"
#include "EdgeDetection.hh"

#define size _MX_size

QImage EdgeDetection::convert(QImage *pic)
{
    Matrix kernel;
    MakeKernel3X3Cross(&kernel);
    
    QImage *tmp = new QImage(Erosion::convert(pic, kernel));
    QImage res = AlgebraicOp::operate(*pic, *tmp, '-');

    delete tmp;

    return res;
}
