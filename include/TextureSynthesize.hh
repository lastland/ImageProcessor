#ifndef _TEXTURESYNTHESIZE_H_
#define _TEXTURESYNTHESIZE_H_

#include <QtGui/QImage>
#include <QtGui/QColor>

class TextureSynthesize
{
public:
    TextureSynthesize();
    virtual ~TextureSynthesize();
    static QImage convert(QImage *pic, int bw, int bh);
private:
    static int errorValue(QRgb a, QRgb b);
    static int errorValue(QImage *a, int asw, int ash,
                          QImage *b, int bsw, int bsh,
                          int w, int h);
    static void copyPartTo(QImage *a, int asw, int ash,
                       QImage *b, int bsw, int bsh,
                           int w, int h, int ow, int oh);
};

#endif /* _TEXTURESYNTHESIZE_H_ */
