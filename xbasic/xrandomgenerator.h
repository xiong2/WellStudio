#ifndef XRANDOMGENERATOR_H
#define XRANDOMGENERATOR_H

#include "xbasic_global.h"
#include <cstdlib>

///@brief The class provides a random number generator
class XBASIC_EXPORT CXRandomGenerator
{
public:
	CXRandomGenerator(bool bUniform = true, unsigned long nValue = rand(), double mu = 0.,double sig=1.);
	~CXRandomGenerator();

	///@brief Get a value between [0, 1] according to the distribution
	float GetValue();

private:
	inline unsigned long long rand64();
	inline double doub();

private:
	bool m_bUniform;
	unsigned long long m_nSeedNum;
	unsigned long long m_u, m_v, m_w;
	double m_mu;
	double m_sig;
	double m_storeval;
	
};

#endif // RLRANDOMGENERATOR_H


