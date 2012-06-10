#include "Kernel.hh"
#include "Dilation.hh"
#include "Erosion.hh"
#include "AlgebraicOp.hh"
#include "Gradient.hh"

#define size kernel_size

QImage Gradient::convert(QImage *pic)
{
    Kernel kernel;
    MakeKernel3X3Cross(&kernel);
    
    QImage dil = Dilation::convert(pic, kernel);
    QImage ero = Erosion::convert(pic, kernel);
    QImage res = AlgebraicOp::operate(dil, ero, '-');

    return res;
}
