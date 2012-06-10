#include "Kernel.hh"
#include "Utility.hh"
#include "Erosion.hh"
#include "Dilation.hh"
#include "Reconstruct.hh"

QImage Reconstruct::convert(QImage *pic)
{
    Kernel kernel;
    QImage T, M;
    
    MakeKernel3X3Cross(&kernel);

    M = Erosion::convert(pic, kernel);
    M = Dilation::convert(&M, kernel);
    
    do
    {
        T = M;
        M = Dilation::convert(&M, kernel);
        Utility::bitwise_and(&M, pic, &M);
    } while (M != T);

    return T;
}
