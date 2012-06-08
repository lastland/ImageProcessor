#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <QtGui/QImage>

class Utility
{
public:
    static bool isBinary(QImage *pic)
    {
        if (!pic->isGrayscale())
            return false;
        for (int i = 0; i < pic->width(); i++)
            for (int j = 0; j < pic->height(); j++)
            {
                if (qGreen(pic->pixel(i, j)) != 0 &&
                    qGreen(pic->pixel(i, j)) != 255)
                    return false;
            }
        return true;
    }
};

#endif /* _UTILITY_H_ */
