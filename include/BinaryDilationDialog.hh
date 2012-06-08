#ifndef _BINARYDILATIONDIALOG_H_
#define _BINARYDILATIONDIALOG_H_

#include "KernelOpDialog.hh"

class BinaryDilationDialog : public KernelOpDialog
{
    Q_OBJECT
public:
    BinaryDilationDialog(QImage *pic, QWidget *parent = NULL, Qt::WindowFlags f = Qt::Dialog);
    virtual ~BinaryDilationDialog(void);
public slots:
    virtual void convert(void);
};

#endif /* _BINARYDILATIONDIALOG_H_ */
