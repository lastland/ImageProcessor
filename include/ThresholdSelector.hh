#ifndef _THRESHOLDSELECTOR_H_
#define _THRESHOLDSELECTOR_H_

#include "ImageHistogram.hh"

class ThresholdSelector
{
public:
    ThresholdSelector(ImageHistogram *histogram)
    {
        double *p = histogram->getYValue();
        for (int i = 0; i < 256; i++)
            pixels[i] = p[i];
    }
    virtual ~ThresholdSelector() {};
    virtual int getThreshold(void) = 0;

protected:
    double pixels[256];
};

#endif /* _THRESHOLDSELECTOR_H_ */
