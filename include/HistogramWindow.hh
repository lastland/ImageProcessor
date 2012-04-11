#ifndef _HISTOGRAMWINDOW_H_
#define _HISTOGRAMWINDOW_H_

#include <QtGui/QDialog>
#include "ImageHistogram.hh"

class HistogramWindow : public QDialog
{
public:
    HistogramWindow(QImage *pic, QWidget *parent = NULL, Qt::WindowFlags f = Qt::Window);
    virtual ~HistogramWindow();

    void resetHistogramPic(QImage *pic);

private:
    ImageHistogram *histogram;
};

#endif /* _HISTOGRAMWINDOW_H_ */
