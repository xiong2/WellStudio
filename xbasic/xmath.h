#pragma once
#include "xbasic_global.h"

namespace XMath
{
double XBASIC_EXPORT NiceInterval(double fromValue, double toValue, int n);
void XBASIC_EXPORT NiceLevel(double dInterval, double dMin, double dMax, double* dFirstLevel, int* n, bool isExpanding = false);

double XBASIC_EXPORT Weight(double v, double vMax, int power);
}
