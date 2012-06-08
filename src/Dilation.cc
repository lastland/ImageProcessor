#include "Utility.hh"
#include "Dilation.hh"

#define size _MX_size

QImage Dilation::convert(QImage *pic, Matrix kernel)
{
    QImage res = QImage(*pic);
    bool binary = Utility::isBinary(pic);

    if (binary)
        for (int i = 0; i < pic->width(); i++)
            for (int j = 0; j < pic->height(); j++)
                res.setPixel(i, j, getMaxFromKernelBin(pic, i, j, kernel));
    else
        for (int i = 0; i < pic->width(); i++)
            for (int j = 0; j < pic->height(); j++)
                res.setPixel(i, j, getMaxFromKernelGray(pic, i, j, kernel));
    
    return res;
}

QRgb Dilation::getMaxFromKernelBin(QImage *pic, int x, int y, Matrix kernel)
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
    
    return pic->pixel(x, y);
}

QRgb Dilation::getMaxFromKernelGray(QImage *pic, int x, int y, Matrix kernel)
{
    int max = 0;
    
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            int u = x + i - size / 2;
            int v = y + j - size / 2;
            if (u < 0 || u >= pic->width() || v < 0 || v >= pic->height())
                continue;
            int value = kernel.value[i][j] + qGreen(pic->pixel(u, v));
            if (value > max) max = value;
        }

    if (max > 255) max = 255;
    return QColor(max, max, max).rgb();
}

