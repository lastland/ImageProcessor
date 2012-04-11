#ifndef _IMAGEHISTOGRAM_H_
#define _IMAGEHISTOGRAM_H_

#include <QtGui/QImage>
#include <QtGui/QWidget>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_histogram.h>

class ImageHistogram : public QWidget
{
public:
    ImageHistogram(QImage *pic, QWidget *parent = NULL);
    
    void resetPic(QImage *pic);
    void replot(void);

    double *getXValue(void);
    double *getYValue(void);
    
    virtual ~ImageHistogram();
private:
    QImage *m_pic;
    QwtPlot *m_plot;
    double m_x[256];
    double m_y[256];

    void imageStatistics(void);
};

#endif /* _IMAGEHISTOGRAM_H_ */
