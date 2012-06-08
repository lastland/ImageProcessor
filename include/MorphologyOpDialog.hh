#ifndef _BINARYDILATIONDIALOG_H_
#define _BINARYDILATIONDIALOG_H_

#include "KernelOpDialog.hh"
#include "ui_MorphologyRadioWidget.h"

class MorphologyOpDialog : public KernelOpDialog
{
    Q_OBJECT
public:
    MorphologyOpDialog(QImage *pic, QWidget *parent = NULL, Qt::WindowFlags f = Qt::Dialog);
    virtual ~MorphologyOpDialog(void);
public slots:
    virtual void convert(void);
private:
    Ui::MorphologyRadioWidget *m_widget;
};

#endif /* _BINARYDILATIONDIALOG_H_ */
