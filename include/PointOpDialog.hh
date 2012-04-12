#ifndef _POINTOPDIALOG_H_
#define _POINTOPDIALOG_H_

#include "ConvertDialog.hh"
#include "ui_PointOpDialog.h"

class PointOpDialog : public ConvertDialog, public Ui::PointOpDialog
{
    Q_OBJECT
public:
    PointOpDialog(QImage *pic, QWidget *parent = NULL, Qt::WindowFlags f = Qt::Window);
    virtual ~PointOpDialog();
public slots:
    virtual void convert(void);
};

#endif /* _POINTOPDIALOG_H_ */
