#include <QtGui/QImage>
#include <QtGui/QColor>
#include "MeanFilter.hh"

#define SCALE 1
#define AVG (1.0 / 9)

QImage MeanFilter::filter(QImage *pic)
{
    QImage opic(*pic);
    QImage npic(*pic);
    for (int i = SCALE; i < opic.width() - SCALE; i++)
        for (int j = SCALE; j < opic.height() - SCALE; j++)
        {
            double r = 0, g = 0, b = 0;
            for (int p = -SCALE; p <= SCALE; p++)
                for (int q = -SCALE; q <= SCALE; q++)
                {
                    r += qRed(opic.pixel(i + p, j + q)) * AVG;
                    g += qGreen(opic.pixel(i + p, j + q)) * AVG;
                    b += qBlue(opic.pixel(i + p, j + q)) * AVG;
                }
            npic.setPixel(i, j, QColor(r, g, b).rgb());
        }
    return npic;
}
