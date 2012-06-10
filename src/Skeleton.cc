#include <QtGui/QColor>
#include "AlgebraicOp.hh"
#include "Kernel.hh"
#include "Utility.hh"
#include "Skeleton.hh"

using namespace std;

QImage Skeleton::convert(QImage *pic, list<QImage> **lst)
{
    Kernel kernel;

    MakeKernel3X3Cross(&kernel);

    delete *lst;
    *lst = new list<QImage>;
    
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
        (*lst)->push_back(*tmp2);
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

QImage Skeleton::restore(QImage *pic, list<QImage> *lst)
{
    int cnt = 1;
    Kernel kernel;
    QImage res = QImage(*pic);
    res.fill(QColor(0, 0, 0).rgb());

    MakeKernel3X3Cross(&kernel);

    for (list<QImage>::iterator iter = lst->begin();
         iter != lst->end(); iter++, cnt++)
    {
        QImage tmp = *iter;
        for (int i = 0; i < cnt; i++)
            tmp = Dilation::convert(&tmp, kernel);
        Utility::bitwise_or(&res, &tmp, &res);
    }

    return res;
}
