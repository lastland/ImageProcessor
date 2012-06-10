#include "DistanceTransform.hh"
#include "DistanceTransformDialog.hh"

DistanceTransformDialog::DistanceTransformDialog(QImage *pic,
                                                 QWidget *parent,
                                                 Qt::WindowFlags f)
    : ConvertDialog(pic, parent, f), Ui::DistanceTransformDialog()
{
    setupUi(this);

    connect(euclideanButton, SIGNAL(clicked()),
            this, SLOT(convert()));
    connect(cityblockButton, SIGNAL(clicked()),
            this, SLOT(convert()));
    connect(chessboardButton, SIGNAL(clicked()),
            this, SLOT(convert()));
}

DistanceTransformDialog::~DistanceTransformDialog(void)
{
}

void DistanceTransformDialog::convert(void)
{
    DistanceMetric metric;
    
    if (euclideanButton->isChecked())
        metric = Euclidean;
    else if (cityblockButton->isChecked())
        metric = CityBlock;
    else
        metric = Chessboard;

    delete m_convertedPic;
    
    m_convertedPic = new QImage(
        DistanceTransform::convert(m_pic, metric));

    emit imageConverted(*m_convertedPic);
}
