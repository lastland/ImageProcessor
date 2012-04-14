/*
 * This class, together with GeometricScale, have something in common that should
 * be combined in the future.
 */
#include <cmath>
#include <QtGui/QColor>
#include <QtGui/QImage>
#include "GeometricRotate.hh"

const double PI = 3.14159265358979;

inline double deg_to_arc(double deg)
{
    return deg / 180 * PI;
}

inline int bilinear_calc(double u, double v, int f1, int f2, int f3, int f4)
{
    double value = (1 - u) * (1 - v) * (double)f1 + u * (1 - v) * (double)f2 +
        (1 - u) * v * (double)f3 + u * v * (double)f4;
    return (int)value;
}

QImage GeometricRotate::convert(QImage *pic, double angle, InterpolationMethod m)
{
    QImage opic(*pic);
    int t = angle / 90;
    double arc = deg_to_arc(angle);
    double cosa = cos(arc);
    double sina = sin(arc);
    int w = abs((double)opic.width() * cosa) + abs((double)opic.height() * sina);
    int h = abs((double)opic.height() * cosa) + abs((double)opic.width() * sina);
    QImage npic(w, h, QImage::Format_ARGB32);

    int dx = ((t == 1 || t == 2) ? (double)opic.width() * cosa : 0) +
        ((t == 2 || t == 3) ? (double)opic.height() * sina : 0);
    int dy = ((t == 1 || t == 2) ? (double)opic.height() * cosa : 0) -
        ((t == 0 || t == 1) ? (double)opic.width() * sina : 0);

    switch (m)
    {
    case NEAREST_NEIGHBOR:
        for (int i = 0; i < w; i++)
            for (int j = 0; j < h; j++)
            {
                int di = i + dx;
                int dj = j + dy;
                int x = (int)((double)di * cosa - (double)dj * sina);
                int y = (int)((double)di * sina + (double)dj * cosa);
                if (x < 0 || x >= opic.width() - 1 ||
                    y < 0 || y >= opic.height() - 1)
                {
                    npic.setPixel(i, j, 0xffffffff);
                    continue;
                }
                npic.setPixel(i, j, opic.pixel(x, y));
            }
        break;
    case BILINEAR:
        for (int i = 0; i < w; i++)
            for (int j = 0; j < h; j++)
            {
                int di = i + dx;
                int dj = j + dy;
                double u = (double)di * cosa - (double)dj * sina;
                double v = (double)di * sina + (double)dj * cosa;
                int x = (int)u;
                int y = (int)v;
                u = u - (double)x;
                v = v - (double)y;

                if (x < 0 || x >= opic.width() - 1 ||
                    y < 0 || y >= opic.height() - 1)
                {
                    npic.setPixel(i, j, 0xffffffff);
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
