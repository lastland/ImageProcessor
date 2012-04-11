#ifndef _CONVOLUTION_H_
#define _CONVOLUTION_H_

#include <QtGui/QImage>

typedef struct _Convolution_Mask
{
    int x;
    int y;
    double value;
} CMask;

class Convolution
{
public:
    static const int MAXSIZE = 10;

    Convolution(CMask mask[MAXSIZE][MAXSIZE], int size1, int size2);
    virtual QImage convolve(QImage *pic, int threshold);
    virtual ~Convolution();
protected:
    CMask m_mask[MAXSIZE][MAXSIZE];
    int m_size1;
    int m_size2;
};

#endif /* _CONVOLUTION_H_ */
