#include "ThresholdSelector.hh"
#include "OtsuThresholder.hh"
#include "EntropyThresholder.hh"
#include "BinaryImage.hh"

BinaryImage::BinaryImage(QImage *pic, QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f), Ui::BinaryImageDialog()
{
    m_pic = new QImage(*pic);
    m_convertedPic = new QImage(*pic);
    m_histogram = new ImageHistogram(pic);
    m_otsu = new OtsuThresholder(m_histogram);
    m_entropy = new EntropyThresholder(m_histogram);
    setupUi(this);
    gridLayout->addWidget(m_histogram, 0, 0);
    connect(thresholdSlider, SIGNAL(valueChanged(int)),
            this, SLOT(getThreshold(int)));
    connect(otsuButton, SIGNAL(clicked()),
            this, SLOT(getOtsuThreshold()));
    connect(entropyButton, SIGNAL(clicked()),
            this, SLOT(getEntropyThreshold()));
    setFixedWidth(250);
    setFixedHeight(400);

    m_threshold = 0;
}

BinaryImage::~BinaryImage()
{
}

void BinaryImage::getOtsuThreshold(void)
{
    m_threshold = m_otsu->getThreshold();
    thresholdSlider->setValue(m_threshold);
    convert();
}

void BinaryImage::getEntropyThreshold(void)
{
    m_threshold = m_entropy->getThreshold();
    thresholdSlider->setValue(m_threshold);
    convert();
}

void BinaryImage::getThreshold(int threshold)
{
    if (m_threshold == threshold)
        return;
    m_threshold = threshold;
    convert();
}

void BinaryImage::convert(void)
{
    for (int i = 0; i < m_convertedPic->width(); i++)
        for (int j = 0; j < m_convertedPic->height(); j++)
        {
            if (qGreen(m_pic->pixel(i, j)) <= m_threshold)
                m_convertedPic->setPixel(i, j, 0xff000000);
            else
                m_convertedPic->setPixel(i, j, 0xffffffff);
        }
    emit imageConverted(*m_convertedPic);
}

void BinaryImage::accept(void)
{
    emit imageConverted(*m_pic);
    emit imageConverted(*m_convertedPic);
    QDialog::accept();
}

void BinaryImage::reject(void)
{
    emit imageConverted(*m_pic);
    emit imageConverted(*m_pic);
    QDialog::reject();
}
