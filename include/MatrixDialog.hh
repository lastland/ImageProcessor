#ifndef _MATRIXDIALOG_H_
#define _MATRIXDIALOG_H_

#include "Kernel.hh"
#include "ConvertDialog.hh"
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QImage>
#include <QtGui/QSpinBox>

#define _MX_size kernel_size

typedef struct Kernel Matrix;

class MatrixDialog : public ConvertDialog
{
public:
    MatrixDialog(int min, int max, int step,
                 QImage *pic = NULL, QWidget *parent = NULL,
                 Qt::WindowFlags f = Qt::Dialog);
    virtual ~MatrixDialog(void);
    void resetMinMaxStep(int min, int max, int step);
    Matrix getMatrix(void);

protected:
    QSpinBox *m_spin[_MX_size][_MX_size];
    QGridLayout *m_gridLayout;
};

#endif /* _MATRIXDIALOG_H_ */
