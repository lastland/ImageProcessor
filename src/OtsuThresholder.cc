#include "OtsuThresholder.hh"

int OtsuThresholder::getThreshold(void)
{
    double sum = 0, pixelNum = 0;
    for (int i = 0; i < 256; i++)
    {
        sum += pixels[i] * i;
        pixelNum += pixels[i];
    }
    double f = -1, threshold = -1;
    double n1 = 0, sum1 = 0;
    for (int i = 0; i < 256; i++)
    {
        n1 += pixels[i];
        sum1 += i * pixels[i];
        double n2 = pixelNum - n1;
        if (n1 == 0 || n2 == 0)
            continue;
        double a = sum1 / n1 - (sum - sum1) / n2;
        double s = n1 * n2 * a * a;
        if (s > f)
        {
            f = s;
            threshold = i;
        }
    }
    return threshold;
}
