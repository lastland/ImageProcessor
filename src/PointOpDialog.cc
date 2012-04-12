#include "ConvertDialog.hh"
#include "PointOpDialog.hh"

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
            int v = qGreen(m_pic->pixel(i, j));
            v = (int)(aSpinBox->value() * (double)v + bSpinBox->value());
            v = v < 255 ? v : 255;
            v = v > 0 ? v : 0;
            m_convertedPic->setPixel(i, j, QColor(v, v, v).rgb());
        }
    emit imageConverted(*m_convertedPic);
}
