#include <cmath>
#include "GaussianMatrix.hh"

#define PI 3.14159265358979

G_Matrix GaussianMatrix::getMatrix(double radius)
{
    G_Matrix matrix;
    double C = 1 / (2 * PI * radius * radius);
    for (int i = 0; i < GAUSS_N; i++)
        for (int j = 0; j < GAUSS_N; j++)
        {
            matrix.v[i][j] = C * exp(-(i * i + j * j) / (2 * radius * radius));
            matrix.v[i][j] = matrix.v[i][j] < 1.0 ? matrix.v[i][j] : 1.0;
            matrix.v[i][j] = matrix.v[i][j] > 0.0 ? matrix.v[i][j] : 0.0;
        }
    return matrix;
}
