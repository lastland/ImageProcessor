#include <iostream>
#include <QtGui/QImage>
#include "TextureSynthesize.hh"

const static int hn = 6;
const static int wn = 6;

#define ABS_DIS(x, y) abs((x) - (y))

inline int abs(int num)
{
    return num > 0 ? num : -num;
}

QImage TextureSynthesize::convert(QImage *pic, int bw, int bh)
{
    int sw = (int)((double)bw * (5.0 / 6.0));
    int sh = (int)((double)bh * (5.0 / 6.0));
    int ow = sw * 6 + (bw - sw), oh = sh * 6 + (bh - sh);
    QImage res(ow, oh, QImage::Format_ARGB32);
    res.fill(0x00000000);
    copyPartTo(&res, 0, 0, pic, 0, 0, sw, sh);
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            int min = -1;
            int mini = 0, minj = 0;
            for (int p = 0; p < pic->width() - bw; p += sw)
            {
                for (int q = 0; q < pic->height() - bh; q += sh)
                {
                    int v = 0;
                    if (i > 0)
                        v += errorValue(&res, sw * i, sh * j,
                                       pic, p, q, bw - sw, bh);
                    if (j > 0)
                        v += errorValue(&res, sw * i, sh * j,
                                        pic, p, q, bw, bh - sh);
                    if (i > 0 && j > 0)
                        v -= errorValue(&res, sw * i, sh * j,
                                        pic, p, q, bw - sw, bh - sh);
                    if (v < min || min == -1)
                    {
                        min = v;
                        mini = p;
                        minj = q;
                    }
                }
            }
            copyPartTo(&res, sw * i, sh * j,
                       pic, mini, minj, bw, bh);
        }
    }
    return res;
}

int TextureSynthesize::errorValue(QImage *a, int asw, int ash,
                                  QImage *b, int bsw, int bsh,
                                  int w, int h)
{
    int res = 0;
    for (int i = 0; i < w; ++i)
    {
        for (int j = 0; j < h; ++j)
        {
            res += errorValue(a->pixel(asw + i, ash + j),
                              b->pixel(bsw + i, bsh + j));
        }
    }
    return res;
}

int TextureSynthesize::errorValue(QRgb a, QRgb b)
{
    return (ABS_DIS(qRed(a), qRed(b)) +
            ABS_DIS(qGreen(a), qGreen(b)) +
            ABS_DIS(qBlue(a), qBlue(b))) / 100;
}

void TextureSynthesize::copyPartTo(QImage *a, int asw, int ash,
                                   QImage *b, int bsw, int bsh,
                                   int w, int h)
{
    for (int i = 0; i < w; ++i)
    {
        for (int j = 0; j < h; ++j)
        {
            a->setPixel(asw + i, ash + j, b->pixel(bsw + i, bsh + j));
        }
    }
}
