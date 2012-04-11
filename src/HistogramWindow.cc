#include <QtGui/QFormLayout>
#include "HistogramWindow.hh"

HistogramWindow::HistogramWindow(QImage *pic, QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
{
    histogram = new ImageHistogram(pic, this);
    setFixedWidth(250);
    setFixedHeight(250);
}

HistogramWindow::~HistogramWindow()
{
}

void HistogramWindow::resetHistogramPic(QImage *pic)
{
    histogram->resetPic(pic);
    histogram->replot();
}
