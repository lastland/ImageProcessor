#include "Utility.hh"
#include "Erosion.hh"

#define size _MX_size

QImage Erosion::convert(QImage *pic, Matrix kernel)
{
    QImage res = QImage(*pic);
    bool binary = Utility::isBinary(pic);

    if (binary)
        for (int i = 0; i < pic->width(); i++)
            for (int j = 0; j < pic->height(); j++)
                res.setPixel(i, j, getMinFromKernelBin(pic, i, j, kernel));
    else
        for (int i = 0; i < pic->width(); i++)
            for (int j = 0; j < pic->height(); j++)
                res.setPixel(i, j, getMinFromKernelGray(pic, i, j, kernel));
        

    return res;
}

QRgb Erosion::getMinFromKernelBin(QImage *pic, int x, int y, Matrix kernel)
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

QRgb Erosion::getMinFromKernelGray(QImage *pic, int x, int y, Matrix kernel)
{
    int min = 255;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            int u = x + i - size / 2;
            int v = y + j - size / 2;
            if (u < 0 || u >= pic->width() || v < 0 || v >= pic->height())
                continue;
            int value = qGreen(pic->pixel(u, v)) - kernel.value[i][j];
            if (value < min) min = value;
        }

    if (min < 0) min = 0;
    return pic->pixel(x, y);
}
