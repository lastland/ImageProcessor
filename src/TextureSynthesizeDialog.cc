#include <iostream>
#include "TextureSynthesize.hh"
#include "TextureSynthesizeDialog.hh"

using namespace std;

TextureSynthesizeDialog::TextureSynthesizeDialog(QImage *pic, QWidget *parent, Qt::WindowFlags f)
    : ConvertDialog(pic, parent, f), Ui::TextureSynthesizeDialog()
{
    setupUi(this);
    inputWidthBox->setMaximum(pic->width());
    inputWidthBox->setMinimum(pic->width());
    inputHeightBox->setMaximum(pic->height());
    inputHeightBox->setMinimum(pic->height());
    blockWidthBox->setMaximum(pic->width());
    blockHeightBox->setMaximum(pic->height());
    blockWidthBox->setMinimum(1);
    blockHeightBox->setMinimum(1);
    blockWidthBox->setValue((int)((double)pic->width() / 4.0));
    blockHeightBox->setValue((int)((double)pic->height() / 4.0));
}

TextureSynthesizeDialog::~TextureSynthesizeDialog()
{
}

void TextureSynthesizeDialog::convert(void)
{
    int blockWidth = blockWidthBox->value();
    int blockHeight = blockHeightBox->value();
    delete m_convertedPic;
    m_convertedPic = new QImage(TextureSynthesize::convert(m_pic, blockWidth, blockHeight));
    emit imageConverted(*m_convertedPic);
}

void TextureSynthesizeDialog::accept(void)
{
    this->convert();
    emit imageConverted(*m_pic);
    emit imageConverted(*m_convertedPic);
    QDialog::accept();
}
