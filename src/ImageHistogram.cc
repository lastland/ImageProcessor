#include <qwt/qwt_plot_curve.h>
#include "Grayscale.hh"
#include "ImageHistogram.hh"

using namespace std;

ImageHistogram::ImageHistogram(QImage *pic, QWidget *parent)
    : QWidget(parent)
{
    m_pic = new QImage(*pic);
    m_plot = new QwtPlot(this);
    m_histogram = new QwtPlotCurve();
    m_histogram->attach(m_plot);

    imageStatistics();
    replot();
}

void ImageHistogram::resetPic(QImage *pic)
{
    delete m_pic;
    m_pic = new QImage(*pic);
    imageStatistics();
}

void ImageHistogram::replot(void)
{
    m_plot->setAxisScale(QwtPlot::xBottom, 0, 255);
    m_plot->setCanvasLineWidth(3);
    
    m_histogram->setSamples(m_x, m_y, 256);
    m_histogram->setStyle(QwtPlotCurve::Sticks);

    m_plot->replot();
}

double *ImageHistogram::getXValue(void)
{
    return m_x;
}

double *ImageHistogram::getYValue(void)
{
    return m_y;
}

ImageHistogram::~ImageHistogram()
{
    delete m_pic;
}

void ImageHistogram::imageStatistics(void)
{
    for (int i = 0; i < 256; i++)
    {
        m_x[i] = i;
        m_y[i] = 0;
    }
    for (int i = 0; i < m_pic->width(); i++)
        for (int j = 0; j < m_pic->height(); j++)
        {
            int value = GrayScale::gray(qRed(m_pic->pixel(i, j)),
                                        qGreen(m_pic->pixel(i, j)),
                                        qBlue(m_pic->pixel(i, j)));
            m_y[value] += 1;
        }
}
