#include <cmath>
#include "EntropyThresholder.hh"

int EntropyThresholder::getThreshold(void)
{
    int threshold = -1;
    double value = 0, sum = 0;
    for (int i = 0; i < 256; i++)
        sum += pixels[i];
    double sum1 = 0;
    for (int i = 0; i < 255; i++)
    {
        double h1 = 0, h2 = 0;
        sum1 += pixels[i];
        for (int j = 0; j <= i; j++)
        {
            double p = pixels[j] / sum1;
            if (p != 0)
                h1 -= p * log(p);
        }
        double sum2 = sum - sum1;
        if (sum1 == 0 || sum2 == 0)
            continue;
        for (int j = i + 1; j < 256; j++)
        {
            double p = pixels[j] / sum2;
            if (p != 0)
                h2 -= p * log(p);
        }
        if (h1 + h2 > value)
        {
            value = h1 + h2;
            threshold = i;
        }
    }
    return threshold;
}
