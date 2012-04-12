#include "ConvertDialog.hh"

ConvertDialog::ConvertDialog(QImage *pic, QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
{
    m_pic = new QImage(*pic);
    m_convertedPic = new QImage(*pic);
}

ConvertDialog::~ConvertDialog()
{
    delete m_pic;
    delete m_convertedPic;
}

void ConvertDialog::accept(void)
{
    emit imageConverted(*m_pic);
    emit imageConverted(*m_convertedPic);
    QDialog::accept();
}

void ConvertDialog::reject(void)
{
    emit imageConverted(*m_pic);
    QDialog::reject();
}
