#ifndef _GRAYSCALE_H_
#define _GRAYSCALE_H_

class GrayScale
{
public:
    GrayScale() {};
    virtual ~GrayScale() {};
    static int gray(int r, int g, int b)
    {
        return (int)((double)r * 0.3 + (double)g * 0.59 + (double)b * 0.11);
    }
};

#endif /* _GRAYSCALE_H_ */
