#include "xmath.h"
#include <cmath>
#include <algorithm>
#include <utility>

double XMath::NiceInterval(double fromValue, double toValue, int n)
{
    double step = (toValue - fromValue) / n;
    if (step == 0.0)
        step = 1.0;

    double sign = step > 0.0 ? 1 : -1;
    step        = fabs(step);

    /* Scale step to 1 - 10 range */
    double scaleFactor = 1.0;
    while (step > 10)
    {
        step /= 10.0;
        scaleFactor *= 10.0;
    }
    while (step < 1)
    {
        step *= 10.0;
        scaleFactor /= 10.0;
    }

    /* Find nice step value */
    if (step > 7.50)
        step = 10.0;
    else if (step > 3.50)
        step = 5.0;
    else if (step > 2.25)
        step = 2.5;
    else if (step > 1.50)
        step = 2.0;
    else
        step = 1.0;

    /* Move step back to user space */
    step = step * sign * scaleFactor;
    return step;
}

void XBASIC_EXPORT XMath::NiceLevel(double dInterval, double dMin, double dMax, double* dFirstLevel, int* n, bool isExpanding)
{
    dInterval = abs(dInterval);

    if (dInterval == 0.0 || dMin == dMax)
        return;

    if (isExpanding)
    {
        *dFirstLevel = floor(dMin / dInterval - 1) * dInterval;
        *n           = static_cast<int>(ceil((dMax - *dFirstLevel) / dInterval + 1));
    }
    else
    {
        *dFirstLevel = ceil(dMin / dInterval + 1) * dInterval;
        *n           = static_cast<int>(floor((dMax - *dFirstLevel) / dInterval - 1));
    }
	++*n;
}

double XMath::Weight(double v, double vMax, int power)
{
	v = std::min(v, vMax);
	v = std::max(v, vMax / 1000);

	return std::pow((1 - v / vMax), power) / (v / vMax);
}
