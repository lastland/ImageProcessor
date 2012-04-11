#include <cmath>
#include <QtGui/QColor>
#include "Convolution.hh"

Convolution::Convolution(CMask mask[10][10], int size1, int size2)
    : m_size1(size1), m_size2(size2)
{
    for (int i = 0; i < size1; i++)
        for (int j = 0; j < size2; j++)
        {
            m_mask[i][j].x = mask[i][j].x;
            m_mask[i][j].y = mask[i][j].y;
            m_mask[i][j].value = mask[i][j].value;
        }
}

Convolution::~Convolution()
{
}

QImage Convolution::convolve(QImage *pic, int threshold)
{
    QImage new_pic(*pic);
    int fi = 0, ti = 0, fj = 0, tj = 0;
    for (int i = 0; i < m_size1; i++)
        for (int j = 0; j < m_size2; j++)
        {
            fi = m_mask[i][j].x < fi ? m_mask[i][j].x : fi;
            ti = m_mask[i][j].x > ti ? m_mask[i][j].x : ti;
            fj = m_mask[i][j].x < fj ? m_mask[i][j].x : fj;
            tj = m_mask[i][j].y > tj ? m_mask[i][j].x : tj;
        }
    for (int i = -fi; i < pic->width() - ti; i++)
        for (int j = -fj; j < pic->height() - tj; j++)
        {
            double gradient = 0;
            for (int p = 0; p < m_size1; p++)
            {
                double r = 0;
                for (int q = 0; q < m_size2; q++)
                    r += qGreen(pic->pixel(i + m_mask[p][q].x, j + m_mask[p][q].y)) *
                        m_mask[p][q].value;
                gradient += r * r;
            }
            gradient = sqrt(gradient);
            if (gradient > threshold)
                new_pic.setPixel(i, j, 0xffffffff);
            else
                new_pic.setPixel(i, j, QColor((int)gradient, (int)gradient, (int)gradient).rgb());
        }
    return new_pic;
}
