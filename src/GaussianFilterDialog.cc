#include <cmath>
#include <QtGui/QColor>
#include "ConvertDialog.hh"
#include "GaussianMatrix.hh"
#include "GaussianFilterDialog.hh"

const int n = GAUSS_N * 2 - 1;

GaussianFilterDialog::GaussianFilterDialog(QImage *pic, QWidget *parent, Qt::WindowFlags f)
    : ConvertDialog(pic, parent, f), Ui::GaussianFilterDialog()
{
    setupUi(this);

    setFixedWidth(194);
    setFixedHeight(79);

    connect(radiusBox, SIGNAL(valueChanged(double)),
            this, SLOT(convert()));
}

GaussianFilterDialog::~GaussianFilterDialog()
{
}

void GaussianFilterDialog::convert(void)
{
    convert(GaussianMatrix::getMatrix(radiusBox->value()));
    emit imageConverted(*m_convertedPic);
}

int GaussianFilterDialog::exec(void)
{
    convert();
    return ConvertDialog::exec();
}

void GaussianFilterDialog::convert(Matrix matrix)
{
    double nmatrix[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            nmatrix[i][j] = matrix.v[abs(GAUSS_N - i - 1)][abs(GAUSS_N - j - 1)];
        }
    
    for (int i = 0; i < m_pic->width(); i++)
        for (int j = 0; j < m_pic->height(); j++)
        {
            double r = 0, g = 0, b = 0;
            for (int p = 0; p < n; p++)
                for (int q = 0; q < n; q++)
                {
                    if (i + p - GAUSS_N < 0 || i + p - GAUSS_N >= m_pic->width() ||
                        j + q - GAUSS_N < 0 || j + q - GAUSS_N >= m_pic->height())
                        continue;
                    r += (double)qRed(m_pic->pixel(i + p - GAUSS_N, j + q - GAUSS_N)) * nmatrix[p][q];
                    g += (double)qGreen(m_pic->pixel(i + p - GAUSS_N, j + q - GAUSS_N)) * nmatrix[p][q];
                    b += (double)qBlue(m_pic->pixel(i + p - GAUSS_N, j + q -GAUSS_N)) * nmatrix[p][q];
                }
            m_convertedPic->setPixel(i, j, QColor((int)r, (int)g, (int)b).rgb());
        }
}
