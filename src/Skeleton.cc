#include <QtGui/QColor>
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
    QImage *tmp = NULL;

    ske->fill(QColor(0, 0, 0).rgb());

    do
    {
        delete tmp;
        
        QImage *tmp2 = new QImage(Erosion::convert(img, kernel));
        tmp = new QImage(Dilation::convert(tmp2, kernel));
        delete tmp2;
        
        Utility::bitwise_not(tmp, tmp);
        Utility::bitwise_and(img, tmp, tmp);
        Utility::bitwise_or(ske, tmp, ske);
        
        delete tmp;
        tmp = img;
        
        img = new QImage(Erosion::convert(tmp, kernel));
    }
    while (!Utility::isBlack(img));

    QImage res = QImage(*ske);

    delete ske;
    delete tmp;
    delete img;

    return res;
}
