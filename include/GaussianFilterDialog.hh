#ifndef _GAUSSIANFILTERDIALOG_H_
#define _GAUSSIANFILTERDIALOG_H_

#include "ConvertDialog.hh"
#include "GaussianMatrix.hh"
#include "ui_GaussianFilterDialog.h"

class GaussianFilterDialog : public ConvertDialog, public Ui::GaussianFilterDialog
{
    Q_OBJECT
public:
    GaussianFilterDialog(QImage *pic, QWidget *parent = NULL, Qt::WindowFlags f = Qt::Window);
    virtual ~GaussianFilterDialog();
public slots:
    virtual void convert(void);
    int exec(void);
private:
    void convert(Matrix matrix);
};

#endif /* _GAUSSIANFILTERDIALOG_H_ */
