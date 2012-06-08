#include "Dilation.hh"
#include "BinaryDilationDialog.hh"

BinaryDilationDialog::BinaryDilationDialog(QImage *pic, QWidget *parent, Qt::WindowFlags f)
    : KernelOpDialog(pic, parent, f)
{
    setWindowTitle(tr("Binary Dilation"));
}

BinaryDilationDialog::~BinaryDilationDialog(void)
{
}

void BinaryDilationDialog::convert(void)
{
    Matrix matrix = getMatrix();
    delete m_convertedPic;
    m_convertedPic = new QImage(
        Dilation::convert(m_pic, matrix));
    emit imageConverted(*m_convertedPic);
}
