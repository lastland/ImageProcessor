#include "KernelOpDialog.hh"
#include <QtGui/QPushButton>
#include <QtGui/QDialogButtonBox>

KernelOpDialog::KernelOpDialog(int min, int max, int step,
                               QImage *pic, QWidget *parent, Qt::WindowFlags f)
    : MatrixDialog(min, max, step, pic, parent, f)
{
    QPushButton *button = new QPushButton(tr("&Preview"), this);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(this);
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
    buttonBox->addButton(button, QDialogButtonBox::ApplyRole);

    m_gridLayout->addWidget(buttonBox, 2, 0);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(convert()));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(button, SIGNAL(clicked()), this, SLOT(convert()));
}

KernelOpDialog::~KernelOpDialog(void)
{
}
