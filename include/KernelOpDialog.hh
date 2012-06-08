#ifndef _KERNELOPDIALOG_H_
#define _KERNELOPDIALOG_H_

#include "MatrixDialog.hh"

class KernelOpDialog : public MatrixDialog
{
public:
    KernelOpDialog(int min, int max, int step,
                   QImage *pic, QWidget *parent = NULL, Qt::WindowFlags f = Qt::Dialog);
    virtual ~KernelOpDialog(void);
};

#endif /* _KERNELOPDIALOG_H_ */
