#ifndef _GAUSSIANMATRIX_H_
#define _GAUSSIANMATRIX_H_

const int GAUSS_N = 3;    
typedef struct
{
    double v[GAUSS_N][GAUSS_N];
} Matrix;

class GaussianMatrix
{
public:
    GaussianMatrix() {};
    virtual ~GaussianMatrix() {};
    
    static Matrix getMatrix(double radius);
};

#endif /* _GAUSSIANMATRIX_H_ */
