#ifndef _BINARYDILATIONDIALOG_H_
#define _BINARYDILATIONDIALOG_H_

#include "KernelOpDialog.hh"

class MorphologyOpDialog : public KernelOpDialog
{
    Q_OBJECT
public:
    MorphologyOpDialog(QImage *pic, QWidget *parent = NULL, Qt::WindowFlags f = Qt::Dialog);
    virtual ~MorphologyOpDialog(void);
public slots:
    virtual void convert(void);
};

#endif /* _BINARYDILATIONDIALOG_H_ */
