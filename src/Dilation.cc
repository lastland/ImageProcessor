#include "Dilation.hh"

#define size _MX_size

QImage Dilation::convert(QImage *pic, Matrix matrix)
{
    QImage res = QImage(*pic);
    for (int i = 0; i < pic->width(); i++)
        for (int j = 0; j < pic->height(); j++)
            res.setPixel(i, j, getMaxFromKernel(pic, i, j, matrix));
    
    return res;
}

QRgb Dilation::getMaxFromKernel(QImage *pic, int x, int y, Matrix kernel)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            int u = x + i - size / 2;
            int v = y + j - size / 2;
            if (u < 0 || u >= pic->width() || v < 0 || v >= pic->height())
                continue;
            if (kernel.value[i][j] == 1 && qGreen(pic->pixel(u, v)) == 255)
                return QColor(255, 255, 255).rgb();
        }
    
    return QColor(0, 0, 0).rgb();
}
