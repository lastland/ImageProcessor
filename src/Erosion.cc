#include "Erosion.hh"

#define size _MX_size

QImage Erosion::convert(QImage *pic, Matrix kernel)
{
    QImage res = QImage(*pic);
    for (int i = 0; i < pic->width(); i++)
        for (int j = 0; j < pic->height(); j++)
            res.setPixel(i, j, getMinFromKernel(pic, i, j, kernel));

    return res;
}

QRgb Erosion::getMinFromKernel(QImage *pic, int x, int y, Matrix kernel)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            int u = x + i - size / 2;
            int v = y + j - size / 2;
            if (u < 0 || u >= pic->width() || v < 0 || v >= pic->height())
                continue;
            if (kernel.value[i][j] == 1 && qGreen(pic->pixel(u, v)) == 0)
                return QColor(0, 0, 0).rgb();
        }
    
    return pic->pixel(x, y);
}
