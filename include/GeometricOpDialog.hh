#ifndef _GEOMETRICOPDIALOG_H_
#define _GEOMETRICOPDIALOG_H_

#include <QtGui/QImage>
#include <QtGui/QDialog>
#include "ui_GeometricOpDialog.h"
#include "ConvertDialog.hh"

class GeometricOpDialog : public ConvertDialog, public Ui::GeometricOpDialog
{
    Q_OBJECT
public:
    GeometricOpDialog(QImage *pic, QWidget *parent = NULL, Qt::WindowFlags f = Qt::Window);
    virtual ~GeometricOpDialog();
public slots:
    virtual void convert(void);
protected slots:
    void setRotationSpinValue(int value);
    void setRotationDialValue(double value);
};

#endif /* _GEOMETRICOPDIALOG_H_ */
