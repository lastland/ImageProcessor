#ifndef _DISTANCETRANSFORMDIALOG_H_
#define _DISTANCETRANSFORMDIALOG_H_

#include <QtGui/QWidget>
#include <QtGui/QImage>
#include "ConvertDialog.hh"
#include "ui_DistanceTransformDialog.h"

class DistanceTransformDialog : public ConvertDialog,
                                public Ui::DistanceTransformDialog
{
    Q_OBJECT
public:
    DistanceTransformDialog(QImage *pic, QWidget *parent = NULL, Qt::WindowFlags f = Qt::Window);
    virtual ~DistanceTransformDialog(void);
public slots:
    virtual void convert(void);
};

#endif /* _DISTANCETRANSFORMDIALOG_H_ */
