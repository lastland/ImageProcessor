#ifndef _PREWITTOPERATOR_H_
#define _PREWITTOPERATOR_H_

#include "RobertsOperator.hh"

class PrewittOperator : public RobertsOperator
{
public:
    PrewittOperator()
        : RobertsOperator()
    {
	mask[0][0].x = -1; mask[0][0].y = -1; mask[0][0].value = -1;
	mask[0][1].x = -1; mask[0][1].y =  0; mask[0][1].value = -1;
	mask[0][2].x = -1; mask[0][2].y =  1; mask[0][2].value = -1;
	mask[0][3].x =  1; mask[0][3].y = -1; mask[0][3].value =  1;
	mask[0][4].x =  1; mask[0][4].y =  0; mask[0][4].value =  1;
	mask[0][5].x =  1; mask[0][5].y =  1; mask[0][5].value =  1;
	
	mask[1][0].x = -1; mask[1][0].y = -1; mask[1][0].value = -1;
	mask[1][1].x =  0; mask[1][1].y = -1; mask[1][1].value = -1;
	mask[1][2].x =  1; mask[1][2].y = -1; mask[1][2].value = -1;
	mask[1][3].x = -1; mask[1][3].y =  1; mask[1][3].value = 1;
	mask[1][4].x =  0; mask[1][4].y =  1; mask[1][4].value = 1;
	mask[1][5].x =  1; mask[1][5].y =  1; mask[1][5].value = 1;
        delete conv;
        conv = new Convolution(mask, size1, size2);
    }
    virtual ~PrewittOperator() {};
protected:
    static const int size1 = 2;
    static const int size2 = 6;
};

#endif /* _PREWITTOPERATOR_H_ */
