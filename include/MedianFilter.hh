#ifndef _MEDIANFILTER_H_
#define _MEDIANFILTER_H_

#include <QtGui/QImage>

class MedianFilter
{
public:
    MedianFilter() {};
    virtual ~MedianFilter() {};
    static QImage filter(QImage *pic);
};

#endif /* _MEDIANFILTER_H_ */
