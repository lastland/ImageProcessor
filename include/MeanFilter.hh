#ifndef _MEANFILTER_H_
#define _MEANFILTER_H_

#include <QtGui/QImage>

class MeanFilter
{
public:
    MeanFilter() {};
    virtual ~MeanFilter() {};
    static QImage filter(QImage *pic);
};

#endif /* _MEANFILTER_H_ */
