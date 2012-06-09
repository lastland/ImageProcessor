#include <list>
#include <cmath>
#include <QtGui/QColor>
#include "DistanceTransform.hh"

using namespace std;

#define abs(x) \
    ((x) < 0 ? -(x) : (x))

#define max(a, b) \
    ((a) > (b) ? (a) : (b))

#define pos(vector, x, y, w, h) \
    vector[(x) * (w) + (y)]

enum {
    NotInPic,
    Edge,
    InPic
};

typedef struct {
    int x;
    int y;
    double v;
} node;

double EuclideanDistance(int dx, int dy)
{
    return sqrt((double)dx * dx + (double)dy * dy);
}

double CityBlockDistance(int dx, int dy)
{
    return (double)abs(dx) + (double)abs(dy);
}

double ChessboardDistance(int dx, int dy)
{
    return (double)max(abs(dx), abs(dy));
}

typedef double (*distanceFuncType)(int dx, int dy);
distanceFuncType distanceFunc[DistanceMetricsCount] = {
    EuclideanDistance, CityBlockDistance, ChessboardDistance};

void DistanceTransform::calDis(QImage *f, double *r, int x, int y, DistanceMetric metric)
{
    list<int> *xs = new list<int>;
    list<int> *ys = new list<int>;
    list<int>::iterator xi;
    list<int>::iterator yi;

    if (qRed(f->pixel(x, y)) == Edge)
        pos(r, x, y, f->width(), f->height()) = 1;
    double here = pos(r, x, y, f->width(), f->height());
    
    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++)
            if (i != 0 || j != 0)
            {
                if (inRange(f, x + i, y + j) && qRed(f->pixel(x + i, y + j)) == InPic &&
                    ((pos(r, x + i, y + j, f->width(), f->height()) > (distanceFunc[metric](i, j) + here)) ||
                     (pos(r, x + i, y + j, f->width(), f->height()) == 0)))
                {
                    pos(r, x + i, y + j, f->width(), f->height()) = distanceFunc[metric](i, j) + here;
                    xs->push_back(x + i);
                    ys->push_back(y + j);
                }
            }

    for (xi = xs->begin(), yi = ys->begin();
         xi != xs->end(); xi++, yi++)
    {
        calDis(f, r, *xi, *yi, metric);
    }

    delete xs;
    delete ys;
}

void DistanceTransform::dij(QImage *f, double *r, DistanceMetric metric)
{
    int w = f->width();
    int h = f->height();
    int leftcnt = 0;
    list<node> accept;
    double *record = new double[w * h];

    for (int i = 0; i < w * h; i++)
        record[i] = -1;

    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
            if (qRed(f->pixel(i, j)) == Edge || qRed(f->pixel(i, j)) == InPic)
            {
                node t = {
                    .x = i,
                    .y = j,
                    .v = 1
                };
                if (qRed(f->pixel(i, j)) == Edge)
                {
                    accept.push_back(t);
                    pos(record, i, j, w, h) = 1;
                }
                else
                {
                    pos(record, i, j, w, h) = 0;
                    leftcnt++;
                }
            }

    while (leftcnt)
    {
        node mininode = {
            .x = 0,
            .y = 0,
            .v = 0
        };
        for (list<node>::iterator iter = accept.begin(); iter != accept.end(); iter++)
        {
            int x = iter->x;
            int y = iter->y;
            double v = iter->v;
            for (int i = -1; i < 2; i++)
                for (int j = -1; j < 2; j++)
                    if ((i != 0 || j != 0) && inRange(f, x + i, y + j) &&
                        pos(record, x + i, y + j, w, h) == 0)
                    {
                        double value = distanceFunc[metric](i, j) + v;
                        if (value < mininode.v || mininode.v == 0)
                        {
                            mininode.x = x + i;
                            mininode.y = y + j;
                            mininode.v = value;
                        }
                    }
        }
        leftcnt--;
        accept.push_back(mininode);
        pos(record, mininode.x, mininode.y, w, h) = 1;
    }

    for (list<node>::iterator iter = accept.begin(); iter != accept.end(); iter++)
        pos(r, iter->x, iter->y, w, h) = iter->v;
}

void DistanceTransform::spfa(QImage *f, double *r, DistanceMetric metric)
{
    list<node> q;
    int w = f->width();
    int h = f->height();
    
    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
            if (qRed(f->pixel(i, j)) == Edge)
            {
                node t = {
                    .x = i,
                    .y = j,
                    .v = 1
                };
                if (qRed(f->pixel(i, j)) == Edge)
                {
                    q.push_back(t);
                    pos(r, i, j, w, h) = 0;
                }
            }

    for (list<node>::iterator iter = q.begin(); iter != q.end(); iter++)
    {
        int x = iter->x;
        int y = iter->y;
        double v = iter->v;
        for (int i = -1; i < 2; i++)
            for (int j = -1; j < 2; j++)
                if ((i != 0 || j != 0) && inRange(f, x + i, y + j) && qRed(f->pixel(x + i, y + j)) == InPic)
                {
                    if (v + distanceFunc[metric](i, j) < pos(r, x + i, y + j, w, h) ||
                        pos(r, x + i, y + j, w, h) == 0)
                    {
                        pos(r, x + i, y + j, w, h) = v + distanceFunc[metric](i, j);
                        node t = {
                            .x = x + i,
                            .y = y + j,
                            .v = pos(r, x + i, y + j, w, h)
                        };
                        q.push_back(t);
                    }
                }
    }
}

QImage DistanceTransform::convert(QImage *pic, DistanceMetric metric)
{
    if (!Utility::isBinary(pic))
    {
        // Well, what should I do?
    }

    QImage *f = new QImage(*pic);
    double *r = new double[pic->width() * pic->height()];
    QImage res = QImage(*pic);

    for (int i = 0; i < pic->width() * pic->height(); i++)
        r[i] = 0;

    for (int i = 0; i < pic->width(); i++)
        for (int j = 0; j < pic->height(); j++)
        {
            if (qGreen(pic->pixel(i, j)) == 255)
            {
                if (isEdge(pic, i, j))
                    f->setPixel(i, j, QColor(Edge, 0, 0).rgb());
                else
                    f->setPixel(i, j, QColor(InPic, 0, 0).rgb());
            }
            else
            {
                f->setPixel(i, j, QColor(NotInPic, 0, 0).rgb());
            }
        }

    spfa(f, r, metric);

    double maximum = 0;
    for (int i = 0; i < pic->width(); i++)
        for (int j = 0; j < pic->height(); j++)
        {
            if (pos(r, i, j, pic->width(), pic->height()) > maximum)
                maximum = pos(r, i, j, pic->width(), pic->height());
        }

    for (int i = 0; i < pic->width(); i++)
        for (int j = 0; j < pic->height(); j++)
        {
            int v;
            if (maximum != 0)
                v = (int)(pos(r, i, j, pic->width(), pic->height()) / maximum * 255);
            else
                v = 0;
            res.setPixel(i, j, QColor(v, v, v).rgb());
        }

    delete f;
    delete[] r;

    return res;
}

bool DistanceTransform::isEdge(QImage *pic, int x, int y)
{
    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++)
            if (i != 0 || j != 0)
            {
                if (inRange(pic, x + i, y + j) && qGreen(pic->pixel(x + i, y + j)) == 0)
                    return true;
            }
    return false;
}

bool DistanceTransform::inRange(QImage *pic, int x, int y)
{
    return !(x < 0 || x >= pic->width() || y < 0 || y >= pic->height());
}
