#ifndef _ROBERTSOPERATOR_H_
#define _ROBERTSOPERATOR_H_

#include "Convolution.hh"

class RobertsOperator
{
public:
    RobertsOperator()
    {
	mask[0][0].x = 0; mask[0][0].y = 0; mask[0][0].value = -1;
	mask[0][1].x = 1; mask[0][1].y = 1; mask[0][1].value =  1;
	mask[1][0].x = 0; mask[1][0].y = 1; mask[1][0].value = -1;
	mask[1][1].x = 1; mask[1][1].y = 0; mask[1][1].value =  1;
        conv = new Convolution(mask, size1, size2);
    }
    QImage convolve(QImage *pic, int threshold)
    {
        return conv->convolve(pic, threshold);
    }
    virtual ~RobertsOperator() {};
protected:
    Convolution *conv;
    static const int size1 = 2;
    static const int size2 = 2;
    CMask mask[Convolution::MAXSIZE][Convolution::MAXSIZE];
};

#endif /* _ROBERTSOPERATOR_H_ */
