#include "Kernel.hh"
#include "Utility.hh"
#include "Erosion.hh"
#include "Dilation.hh"
#include "Reconstruct.hh"

QImage Reconstruct::convert(QImage *pic, ReconstructMethod method)
{
    Kernel kernel;
    QImage T, M;
    bool binary = Utility::isBinary(pic);

    if (binary)
        MakeKernel3X3Cross(&kernel);
    else
        MakeKernelZero(&kernel);

    switch(method)
    {
    case OBR:
        M = Erosion::convert(pic, kernel);
        M = Dilation::convert(&M, kernel);
        break;
    case CBR:
        M = Dilation::convert(pic, kernel);
        M = Erosion::convert(&M, kernel);
        break;
    }
        
    do
    {
        T = M;
        M = Dilation::convert(&M, kernel);
        if (binary)
            Utility::bitwise_and(&M, pic, &M);
        else
            Utility::mask(&M, pic, &M);
    } while (M != T);

    return T;
}
