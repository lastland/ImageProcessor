#include "Dilation.hh"
#include "Erosion.hh"
#include "MorphologyOpDialog.hh"

#define size _MX_size

MorphologyOpDialog::MorphologyOpDialog(QImage *pic, QWidget *parent, Qt::WindowFlags f)
    : KernelOpDialog(pic, parent, f)
{
    m_widget = new Ui::MorphologyRadioWidget;
    QWidget* qwidget = new QWidget;
    m_widget->setupUi(qwidget);
    m_gridLayout->addWidget(qwidget, 1, 0);

    // Set up a default kernel.
    m_spin[size / 2][size / 2]->setValue(1);
    m_spin[size / 2 - 1][size / 2]->setValue(1);
    m_spin[size / 2][size / 2 - 1]->setValue(1);
    m_spin[size / 2 + 1][size / 2]->setValue(1);
    m_spin[size / 2][size / 2 + 1]->setValue(1);

    setWindowTitle(tr("Morphology Operations"));
}

MorphologyOpDialog::~MorphologyOpDialog(void)
{
}

void MorphologyOpDialog::convert(void)
{
    Matrix matrix = getMatrix();
    delete m_convertedPic;
    if (m_widget->dilationButton->isChecked())
        m_convertedPic = new QImage(
            Dilation::convert(m_pic, matrix));
    else if (m_widget->erosionButton->isChecked())
        m_convertedPic = new QImage(
            Erosion::convert(m_pic, matrix));
    else if (m_widget->openingButton->isChecked())
    {
        QImage *tmp = new QImage(
            Erosion::convert(m_pic, matrix));
        m_convertedPic = new QImage(
            Dilation::convert(tmp, matrix));
        delete tmp;
    }
    else
    {
        QImage *tmp = new QImage(
            Dilation::convert(m_pic, matrix));
        m_convertedPic = new QImage(
            Erosion::convert(tmp, matrix));
        delete tmp;
    }
    emit imageConverted(*m_convertedPic);
}
