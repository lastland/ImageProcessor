#ifndef _OTSUTHRESHOLDER_H_
#define _OTSUTHRESHOLDER_H_

#include "ImageHistogram.hh"
#include "ThresholdSelector.hh"

class OtsuThresholder : public ThresholdSelector
{
public:
    OtsuThresholder(ImageHistogram *histogram)
        : ThresholdSelector(histogram) {};
    virtual ~OtsuThresholder() {};
    virtual int getThreshold(void);
};

#endif /* _OTSUTHRESHOLDER_H_ */
