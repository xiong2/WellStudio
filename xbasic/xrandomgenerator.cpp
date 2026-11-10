#include "xrandomgenerator.h"

CXRandomGenerator::CXRandomGenerator(bool bUniform, unsigned long nValue, double mu, double sig)
    :m_bUniform(bUniform), m_nSeedNum(nValue),
     m_v(4101842887655102017LL),
     m_w(1),
     m_mu(mu),
     m_sig(sig),
     m_storeval(0.)
{
    m_u = m_nSeedNum ^ m_v;
    rand64();
    m_v = m_u;
    rand64();
    m_w = m_v;
    rand64();
}

CXRandomGenerator::~CXRandomGenerator()
{
}

float CXRandomGenerator::GetValue()
{
    if (m_bUniform) return static_cast<float>(doub());
	
	double v1, v2, rsq, fac;

	if (m_storeval == 0.)
	{
		do
		{
			v1 = 2.0*doub() - 1.0;
			v2 = 2.0*doub() - 1.0;
			rsq = v1*v1+v2*v2;
		}while (rsq >= 1.0 || rsq == 0.0);

		fac = sqrt(-2.0*log(rsq)/rsq);
		m_storeval = v1*fac;
		return static_cast<float>(m_mu + m_sig*v2*fac);
	}

	fac = m_storeval;
	m_storeval = 0.;
	return static_cast<float>(m_mu + m_sig*fac);
}

unsigned long long CXRandomGenerator::rand64()
{
	m_u = m_u * 2862933555777941757LL + 7046029254386353087LL;

	m_v ^= m_v >> 17;
	m_v ^= m_v << 31; 
	m_v ^= m_v >> 8;

	m_w = 4294957665LL * (m_w & 0xffffffff) + (m_w >>32);

	unsigned long long x = m_u ^(m_u <<21);
	x ^= x >> 35;
	x ^= x << 4;

	return (x + m_v) ^ m_w;
}

double CXRandomGenerator::doub()
{
	return 5.42101086242752217E-20*rand64();
}