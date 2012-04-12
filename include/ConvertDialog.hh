#ifndef _CONVERTDIALOG_H_
#define _CONVERTDIALOG_H_

#include <QtGui/QDialog>
#include <QtGui/QImage>

class ConvertDialog : public QDialog
{
    Q_OBJECT
public:
    ConvertDialog(QImage *pic, QWidget *parent = NULL, Qt::WindowFlags f = Qt::Dialog);
    virtual ~ConvertDialog();
signals:
    void imageConverted(QImage pic);
public slots:
    virtual void accept(void);
    virtual void reject(void);
    virtual void convert(void) = 0;
protected:
    QImage *m_pic;
    QImage *m_convertedPic;
};

#endif /* _CONVERTDIALOG_H_ */
