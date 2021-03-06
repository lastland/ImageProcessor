#include "GeometricScale.hh"
#include "GeometricRotate.hh"
#include "GeometricOpDialog.hh"

GeometricOpDialog::GeometricOpDialog(QImage *pic, QWidget *parent, Qt::WindowFlags f)
    : ConvertDialog(pic, parent, f), Ui::GeometricOpDialog()
{
    setupUi(this);

    connect(rotateDial, SIGNAL(valueChanged(int)),
            this, SLOT(setRotationSpinValue(int)));
    connect(rotateBox, SIGNAL(valueChanged(double)),
            this, SLOT(setRotationDialValue(double)));

    connect(scaleXBox, SIGNAL(valueChanged(double)),
            this, SLOT(convert()));
    connect(scaleYBox, SIGNAL(valueChanged(double)),
            this, SLOT(convert()));
    connect(rotateBox, SIGNAL(valueChanged(double)),
            this, SLOT(convert()));
    connect(nearestNeighborButton, SIGNAL(clicked()),
            this, SLOT(convert()));
    connect(bilinearButton, SIGNAL(clicked()),
            this, SLOT(convert()));

    setFixedWidth(226);
    setFixedHeight(332);
}

GeometricOpDialog::~GeometricOpDialog()
{
}

void GeometricOpDialog::convert(void)
{
    QImage *tmp = NULL;
    delete m_convertedPic;
    InterpolationMethod m = bilinearButton->isChecked() ? BILINEAR : NEAREST_NEIGHBOR;
    tmp = new QImage(
        GeometricScale::convert(m_pic, scaleXBox->value(), scaleYBox->value(), m));
    m_convertedPic = new QImage(
        GeometricRotate::convert(tmp, rotateBox->value(), m));
    delete tmp;
    emit imageConverted(*m_convertedPic);
}

void GeometricOpDialog::setRotationSpinValue(int value)
{
    if ((int)rotateBox->value() != value)
        rotateBox->setValue((double)value);
}

void GeometricOpDialog::setRotationDialValue(double value)
{
    if ((int)value != rotateDial->value())
        rotateDial->setValue((int)value);
}
