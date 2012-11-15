#include <iostream>
#include <QtGui/QImage>
#include "TextureSynthesize.hh"

const static int hn = 12;
const static int wn = 12;

#define ABS_DIS(x, y) abs((x) - (y))

inline int abs(int num)
{
    return num > 0 ? num : -num;
}

QImage TextureSynthesize::convert(QImage *pic, int bw, int bh)
{
    int sw = (int)((double)bw * (5.0 / 6.0));
    int sh = (int)((double)bh * (5.0 / 6.0));
    int ow = sw * 12 + (bw - sw), oh = sh * 12 + (bh - sh);
    QImage res(ow, oh, QImage::Format_ARGB32);
    res.fill(0x00000000);
    copyPartTo(&res, 0, 0, pic, 0, 0, sw, sh, 0, 0);
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
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
                       pic, mini, minj, bw, bh,
                       bw - sw, bh - sh);
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
    return ABS_DIS(qRed(a), qRed(b)) +
        ABS_DIS(qGreen(a), qGreen(b)) +
        ABS_DIS(qBlue(a), qBlue(b));
}

void TextureSynthesize::copyPartTo(QImage *a, int asw, int ash,
                                   QImage *b, int bsw, int bsh,
                                   int w, int h, int ow, int oh)
{
    bool *flag = new bool[w * h];
    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
            flag[j * w + i] = true;
    /*
      The following code would be utimatily ugly,
      for I don't want to use my brain while writing this.
     */
    if (ash > 0)
    {
        int *f = new int[w * oh];
        int *p = new int[w * oh];
        int *e = new int[w];
        for (int i = 0; i < oh; ++i)
        {
            f[i * w] = errorValue(a->pixel(asw, ash + i), b->pixel(bsw, bsh + i));
        }
        for (int i = 1; i < w; ++i)
        {
            for (int j = 0; j < oh; ++j)
            {
                int t = i + j * w;
                f[t] = f[t - 1];
                p[t] = t - 1;
                if (j > 0 && f[t - 1 - w] < f[t])
                {
                    f[t] = f[t - 1 - w];
                    p[t] = t - 1 - w;
                }
                if (j < oh - 1 && f[t - 1 + w] < f[t])
                {
                    f[t] = f[t - 1 + w];
                    p[t] = t - 1 + w;
                }
                f[t] += errorValue(a->pixel(asw + i, ash + j),
                                   b->pixel(bsw + i, bsh + j));
            }
        }
        int min = f[w - 1];
        e[w - 1] = w - 1;
        for (int i = 2; i < oh + 1; ++i)
        {
            if (f[i * w - 1] < min)
            {
                min = f[i * w - 1];
                e[w - 1] = i * w - 1;
            }
        }
        for (int i = w - 2; i >= 0; --i)
        {
            e[i] = p[e[i + 1]];
        }
        for (int i = 0; i < w; i++)
            for (int j = 0; j < e[i] / w; j++)
            {
                flag[j * w + i] = false;
            }
        delete[] f;
        delete[] p;
        delete[] e;
    }

    if (asw > 0)
    {
        int *f = new int[ow * h];
        int *p = new int[ow * h];
        int *e = new int[w];
        for (int i = 0; i < ow; ++i)
        {
            f[i * h] = errorValue(a->pixel(asw + i, ash),
                                  b->pixel(bsw + i, bsh));
        }
        for (int i = 1; i < h; ++i)
        {
            for (int j = 0; j < ow; ++j)
            {
                int t = i + j * h;
                f[t] = f[t - 1];
                p[t] = t - 1;
                if (j > 0 && f[t - 1 - h] < f[t])
                {
                    f[t] = f[t - 1 - h];
                    p[t] = t - 1 - h;
                }
                if (j < ow - 1 && f[t - 1 + h] < f[t])
                {
                    f[t] = f[t - 1 + h];
                    p[t] = t - 1 + h;
                }
                f[t] += errorValue(a->pixel(asw + i, ash + j),
                                   b->pixel(bsw + i, bsh + j));
            }
        }
        int min = f[h - 1];
        e[h - 1] = h - 1;
        for (int i = 2; i < ow + 1; ++i)
        {
            if (f[i * h - 1] < min)
            {
                min = f[i * h - 1];
                e[w - 1] = i * h - 1;
            }
        }
        for (int i = h - 2; i >= 0; --i)
        {
            e[i] = p[e[i + 1]];
        }
        for (int i = 0; i < h; i++)
            for (int j = 0; j < e[i] / h; j++)
            {
                flag[i * w + j] = false;
            }
        delete[] f;
        delete[] p;
        delete[] e;
    }

    for (int i = 0; i < w; ++i)
    {
        for (int j = 0; j < h; ++j)
        {
            if (flag[j * w + i])
            {
                a->setPixel(asw + i, ash + j, b->pixel(bsw + i, bsh + j));
            }
        }
    }
    delete[] flag;
}
