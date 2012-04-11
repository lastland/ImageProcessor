#ifndef _ENTROPYTHRESHOLDER_H_
#define _ENTROPYTHRESHOLDER_H_

#include "ThresholdSelector.hh"

class EntropyThresholder : public ThresholdSelector
{
public:
    EntropyThresholder(ImageHistogram *histogram)
        : ThresholdSelector(histogram) {};
    virtual ~EntropyThresholder() {};
    virtual int getThreshold(void);
};

#endif /* _ENTROPYTHRESHOLDER_H_ */
