#include <cstring>
#include <QtGui/QImage>
#include <QtGui/QColor>
#include "MedianFilter.hh"

#define SCALE 1
#define TOTAL 9
#define MEDIAN ((TOTAL + 1) / 2)

inline void insert(int* a, int value)
{
    if (value >= a[MEDIAN - 1])
        return;

    int i;
    for (i = MEDIAN - 2; i >= 0 && (value <= a[i] || a[i] > 255); i--)
        a[i + 1] = a[i];
    a[i + 1] = value;
}

QImage MedianFilter::filter(QImage *pic)
{
    QImage opic(*pic);
    QImage npic(*pic);
    int ar[MEDIAN], ag[MEDIAN], ab[MEDIAN]; 
    for (int i = SCALE; i < opic.width() - SCALE; i++)
        for (int j = SCALE; j < opic.height() - SCALE; j++)
        {
            memset(ar, 1, sizeof(ar));
            memset(ag, 1, sizeof(ag));
            memset(ab, 1, sizeof(ab));
            for (int p = -SCALE; p <= SCALE; p++)
                for (int q = -SCALE; q <= SCALE; q++)
                {
                    insert(ar, qRed(opic.pixel(i + p, j + q)));
                    insert(ag, qGreen(opic.pixel(i + p, j + q)));
                    insert(ab, qBlue(opic.pixel(i + p, j + q)));
                }
            npic.setPixel(i, j, QColor(ar[MEDIAN - 1], ag[MEDIAN - 1], ab[MEDIAN - 1]).rgb());
        }
    return npic;
}
