#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <QtGui/QImage>
#include <QtGui/QColor>

#define iter_pic(i, j, pic) \
    for (int i = 0; i < pic->width(); i++) \
        for (int j = 0; j < pic->height(); j++)

class Utility
{
public:
    static bool isBinary(QImage *pic)
    {
        if (!pic->isGrayscale())
            return false;
        iter_pic(i, j, pic)
        {
            if (qGreen(pic->pixel(i, j)) != 0 &&
                qGreen(pic->pixel(i, j)) != 255)
                return false;
        }
        return true;
    }

    static bool isBlack(QImage *pic)
    {
        iter_pic(i, j, pic)
        {
            if (qGreen(pic->pixel(i, j)) != 0)
                return false;
        }
        return true;
    }

    static void bitwise_not(QImage *pic, QImage *res)
    {
        iter_pic(i, j, pic)
        {
            if (qGreen(pic->pixel(i, j)) == 0)
                res->setPixel(i, j, QColor(255, 255, 255).rgb());
            else
                res->setPixel(i, j, QColor(0, 0, 0).rgb());
        }
    }

    static void bitwise_and(QImage *a, QImage *b, QImage *res)
    {
        iter_pic(i, j, a)
        {
            if (qGreen(a->pixel(i, j)) == 255 &&
                qGreen(b->pixel(i, j)) == 255)
                res->setPixel(i, j, QColor(255, 255, 255).rgb());
            else
                res->setPixel(i, j, QColor(0, 0, 0).rgb());
        }
    }

    static void bitwise_or(QImage *a, QImage *b, QImage *res)
    {
        iter_pic(i, j, a)
        {
            if (qGreen(a->pixel(i, j)) == 0 &&
                qGreen(b->pixel(i, j)) == 0)
                res->setPixel(i, j, QColor(0, 0, 0).rgb());
            else
                res->setPixel(i, j, QColor(255, 255, 255).rgb());
        }
    }

    static void mask(QImage *pic, QImage *mask_pic, QImage *res)
    {
        iter_pic(i, j, pic)
        {
            QRgb a = pic->pixel(i, j);
            QRgb b = mask_pic->pixel(i, j);
            res->setPixel(i, j, qGreen(a) < qGreen(b) ? a : b);
        }
    }
};

#endif /* _UTILITY_H_ */
