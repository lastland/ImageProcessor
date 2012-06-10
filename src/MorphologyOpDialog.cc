#include "Utility.hh"
#include "Dilation.hh"
#include "Erosion.hh"
#include "MorphologyOpDialog.hh"

#define size _MX_size

MorphologyOpDialog::MorphologyOpDialog(QImage *pic, QWidget *parent, Qt::WindowFlags f)
    : KernelOpDialog(0, 1, 1, pic, parent, f)
{
    int min = 0, max = 1, step = 1;
    if (!Utility::isBinary(pic))
    {
        min = 0;
        max = 255;
        step = 1;
        resetMinMaxStep(min, max, step);
    }
    
    m_widget = new Ui::MorphologyRadioWidget;
    QWidget* qwidget = new QWidget;
    m_widget->setupUi(qwidget);
    m_gridLayout->addWidget(qwidget, 1, 0);

    // Set up a default kernel.
    int defval = max == 1 ? 1 : 0;
    m_spin[size / 2][size / 2]->setValue(defval);
    m_spin[size / 2 - 1][size / 2]->setValue(defval);
    m_spin[size / 2][size / 2 - 1]->setValue(defval);
    m_spin[size / 2 + 1][size / 2]->setValue(defval);
    m_spin[size / 2][size / 2 + 1]->setValue(defval);

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
