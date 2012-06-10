#include "MatrixDialog.hh"
#include <QtGui/QGroupBox>

#define size _MX_size

MatrixDialog::MatrixDialog(int min, int max, int step,
                           QImage *pic, QWidget *parent, Qt::WindowFlags f)
    : ConvertDialog(pic, parent, f)
{
    m_gridLayout = new QGridLayout(this);
    QGroupBox *groupBox = new QGroupBox(this);
    groupBox->setTitle("Kernel");
    QGridLayout* gridLayout = new QGridLayout(groupBox);
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            m_spin[i][j] = new QSpinBox();
            m_spin[i][j]->setMinimum(min);
            m_spin[i][j]->setMaximum(max);
            m_spin[i][j]->setSingleStep(step);
            gridLayout->addWidget(m_spin[i][j], i, j);
        }
    m_gridLayout->addWidget(groupBox);
}

MatrixDialog::~MatrixDialog(void)
{
}

void MatrixDialog::resetMinMaxStep(int min, int max, int step)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            m_spin[i][j]->setMinimum(min);
            m_spin[i][j]->setMaximum(max);
            m_spin[i][j]->setSingleStep(step);
        }
}

Matrix MatrixDialog::getMatrix(void)
{
    Matrix matrix;
    
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            matrix.value[i][j] = m_spin[i][j]->value();

    return matrix;
}
