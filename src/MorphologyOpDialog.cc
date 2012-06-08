#include "Dilation.hh"
#include "MorphologyOpDialog.hh"
#include "ui_MorphologyRadioWidget.h"

MorphologyOpDialog::MorphologyOpDialog(QImage *pic, QWidget *parent, Qt::WindowFlags f)
    : KernelOpDialog(pic, parent, f)
{
    Ui::MorphologyRadioWidget widget;
    QWidget* qwidget = new QWidget;
    widget.setupUi(qwidget);
    m_gridLayout->addWidget(qwidget, 1, 0);
    adjustSize();

    setWindowTitle(tr("Morphology Operations"));
}

MorphologyOpDialog::~MorphologyOpDialog(void)
{
}

void MorphologyOpDialog::convert(void)
{
    Matrix matrix = getMatrix();
    delete m_convertedPic;
    m_convertedPic = new QImage(
        Dilation::convert(m_pic, matrix));
    emit imageConverted(*m_convertedPic);
}
