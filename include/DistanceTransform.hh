#ifndef _DISTANCETRANSFORM_H_
#define _DISTANCETRANSFORM_H_

#include <QtGui/QImage>
#include "Utility.hh"

typedef enum {
    Euclidean,
    CityBlock,
    Chessboard,
    DistanceMetricsCount
} DistanceMetric;

class DistanceTransform
{
public:
    static QImage convert(QImage *pic, DistanceMetric metric);
private:
    static bool isEdge(QImage *pic, int x, int y);
    static bool inRange(QImage *pic, int x, int y);
    static void calDis(QImage *f, double *r, int x, int y, DistanceMetric metric);
    static void dij(QImage *f, double *r, DistanceMetric metric);
    static void spfa(QImage *f, double *r, DistanceMetric metric);
};

#endif /* _DISTANCETRANSFORM_H_ */
