#include "ConvertDialog.hh"
#include "PointOpDialog.hh"

inline void color_range(int *a)
{
    *a = *a < 255 ? *a : 255;
    *a = *a > 0 ? *a : 0;
}

PointOpDialog::PointOpDialog(QImage *pic, QWidget *parent, Qt::WindowFlags f)
    : ConvertDialog(pic, parent, f), Ui::PointOpDialog()
{
    setupUi(this);

    connect(aSpinBox, SIGNAL(valueChanged(double)),
            this, SLOT(convert()));
    connect(bSpinBox, SIGNAL(valueChanged(double)),
            this, SLOT(convert()));

    setFixedWidth(250);
    setFixedHeight(300);
}

PointOpDialog::~PointOpDialog()
{
}

void PointOpDialog::convert(void)
{
    for (int i = 0; i < m_pic->width(); i++)
        for (int j = 0; j < m_pic->height(); j++)
        {
            int r = qRed(m_pic->pixel(i, j));
            int g = qGreen(m_pic->pixel(i, j));
            int b = qBlue(m_pic->pixel(i, j));
            r = (int)(aSpinBox->value() * (double)r + bSpinBox->value());
            g = (int)(aSpinBox->value() * (double)g + bSpinBox->value());
            b = (int)(aSpinBox->value() * (double)b + bSpinBox->value());
            color_range(&r);
            color_range(&g);
            color_range(&b);
            m_convertedPic->setPixel(i, j, QColor(r, g, b).rgb());
        }
    emit imageConverted(*m_convertedPic);
}
