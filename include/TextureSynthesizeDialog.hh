#ifndef _TEXTURESYNTHESIZEDIALOG_H_
#define _TEXTURESYNTHESIZEDIALOG_H_

#include <QtGui/QImage>
#include "ConvertDialog.hh"
#include "ui_TextureSynthesizeDialog.h"

class TextureSynthesizeDialog : public ConvertDialog, public Ui::TextureSynthesizeDialog
{
    Q_OBJECT
public:
    TextureSynthesizeDialog(QImage *pic, QWidget *parent = NULL, Qt::WindowFlags f = Qt::Window);
    virtual ~TextureSynthesizeDialog();
public slots:
    virtual void accept(void);
    virtual void convert(void);
};

#endif /* _TEXTURESYNTHESIZEDIALOG_H_ */
