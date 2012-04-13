#include <QtGui/QColor>
#include <QtGui/QImage>
#include "GeometricScale.hh"

inline int bilinear_calc(double u, double v, int f1, int f2, int f3, int f4)
{
    double value = (1 - u) * (1 - v) * (double)f1 + u * (1 - v) * (double)f2 +
        (1 - u) * v * (double)f3 + u * v * (double)f4;
    return (int)value;
}

QImage GeometricScale::convert(QImage *pic, double sx, double sy, InterpolationMethod m)
{
    QImage opic(*pic);
    int nx = (int)((double)opic.width() * sx);
    int ny = (int)((double)opic.height() * sy);
    QImage npic(nx, ny, QImage::Format_ARGB32);

    switch (m)
    {
    case NEAREST_NEIGHBOR:
        for (int i = 0; i < nx; i++)
            for (int j = 0; j < ny; j++)
                npic.setPixel(i, j,
                              opic.pixel((int)(((double)i + 0.5) / sx),
                                         (int)(((double)j + 0.5) / sy)));
        break;
    case BILINEAR:
        for (int i = 0; i < nx; i++)
            for (int j = 0; j < ny; j++)
            {
                double u = (double)i / sx;
                double v = (double)j / sy;
                int x = (int)u;
                int y = (int)v;
                u = u - (double)x;
                v = v - (double)y;

                if (x < 0 || x >= opic.width() - 1 ||
                    y < 0 || y >= opic.height() - 1)
                {
                    npic.setPixel(i, j,
                                  opic.pixel((int)((double)i / sx),
                                             (int)((double)j / sy)));
                    continue;
                }

                QRgb f1 = opic.pixel(x, y);
                QRgb f2 = opic.pixel(x + 1, y);
                QRgb f3 = opic.pixel(x, y + 1);
                QRgb f4 = opic.pixel(x + 1, y + 1);
                int r = bilinear_calc(u, v, qRed(f1), qRed(f2), qRed(f3), qRed(f4));
                int g = bilinear_calc(u, v, qGreen(f1), qGreen(f2), qGreen(f3), qGreen(f4));
                int b = bilinear_calc(u, v, qBlue(f1), qBlue(f2), qBlue(f3), qBlue(f4));
                
                npic.setPixel(i, j, qRgb(r, g, b));
            }
        break;
    default:
        break;
    }
    
    return npic;
}
