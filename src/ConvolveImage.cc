#include "ConvolveImage.hh"

ConvolveImage::ConvolveImage(QImage *pic, QWidget *parent, Qt::WindowFlags f)
    : BinaryImage(pic, parent, f)
{
    setWindowTitle(tr("Convert to Convolved Image"));
    
    convolutionBox = new QGroupBox(tr("Operator"));
    robertsButton = new QRadioButton(tr("Roberts"));
    prewittButton = new QRadioButton(tr("Prewitt"));
    sobelButton = new QRadioButton(tr("Sobel"));
    
    convolutionLayout = new QVBoxLayout();
    convolutionLayout->addWidget(robertsButton);
    convolutionLayout->addWidget(prewittButton);
    convolutionLayout->addWidget(sobelButton);

    convolutionBox->setLayout(convolutionLayout);
    
    gridLayout->addWidget(convolutionBox, 3, 0, 1, 1);
    gridLayout->addWidget(buttonBox, 4, 0, 1, 1);
    setFixedWidth(250);
    setFixedHeight(500);

    robertsButton->setChecked(true);
    connect(robertsButton, SIGNAL(clicked()),
            this, SLOT(convert()));
    connect(prewittButton, SIGNAL(clicked()),
            this, SLOT(convert()));
    connect(sobelButton, SIGNAL(clicked()),
            this, SLOT(convert()));

    roberts = new RobertsOperator;
    prewitt = new PrewittOperator;
    sobel = new SobelOperator;
}

ConvolveImage::~ConvolveImage()
{
    delete roberts;
    delete prewitt;
    delete sobel;
}

void ConvolveImage::convert(void)
{
    delete m_convertedPic;
    if (robertsButton->isChecked())
        m_convertedPic = new QImage(roberts->convolve(m_pic, m_threshold));
    else if (prewittButton->isChecked())
        m_convertedPic = new QImage(prewitt->convolve(m_pic, m_threshold));
    else
        m_convertedPic = new QImage(sobel->convolve(m_pic, m_threshold));
    emit imageConverted(*m_convertedPic);
}
