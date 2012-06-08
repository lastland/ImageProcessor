#ifndef _MATRIXDIALOG_H_
#define _MATRIXDIALOG_H_

#include "ConvertDialog.hh"
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QImage>
#include <QtGui/QSpinBox>

const int _MX_size = 5;

typedef struct
{
    int value[_MX_size][_MX_size];
} Matrix;

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
