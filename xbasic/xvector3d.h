#ifndef XVECTOR3D_H
#define XVECTOR3D_H


#include "xbasic_global.h"
#include <cmath>

class XBASIC_EXPORT CXVector3D
{
public:
	CXVector3D(double x = 0, double y = 0, double z = 0) { m_vec[0] = x; m_vec[1] = y; m_vec[2] = z; }

	CXVector3D(const double v[3]) { m_vec[0] = v[0]; m_vec[1] = v[1]; m_vec[2] = v[2]; }

	CXVector3D(const CXVector3D& v) { m_vec[0] = v.m_vec[0]; m_vec[1] = v.m_vec[1]; m_vec[2] = v.m_vec[2]; }

	CXVector3D(const CXVector3D& v1, const CXVector3D& v2) 
	{
		m_vec[0] = v2.m_vec[0] - v1.m_vec[0];
		m_vec[1] = v2.m_vec[1] - v1.m_vec[1];
		m_vec[2] = v2.m_vec[2] - v1.m_vec[2];
	}
	~CXVector3D(void) {}
	
	///@brief Get the length
	double Length() const { return sqrt(m_vec[0] * m_vec[0] + m_vec[1] * m_vec[1] + m_vec[2] * m_vec[2]); }

	///@brief Normalize
	void Normalize() 
	{
		double len = Length();
		m_vec[0] /= len; m_vec[1] /= len; m_vec[2] /= len;
	}

	///brief Set value
	void SetValue(const double v[3]) { m_vec[0] = v[0]; m_vec[1] = v[1]; m_vec[2] = v[2]; }
	void SetValue(double x, double y, double z) { m_vec[0] = x; m_vec[1] = y; m_vec[2] = z; }

	///@brief Dot and  cross
	double  Dot(const CXVector3D& v) const {return m_vec[0] * v.m_vec[0] + m_vec[1] * v.m_vec[1] + m_vec[2] * v.m_vec[2];	}

	CXVector3D Cross(const CXVector3D& v) const
	{
		return CXVector3D(	m_vec[1] * v.m_vec[2] - m_vec[2] * v.m_vec[1],
							m_vec[2] * v.m_vec[0] - m_vec[0] * v.m_vec[2],
							m_vec[0] * v.m_vec[1] - m_vec[1] * v.m_vec[0]);
	}

	//Operators
	double& operator [](int i) { return (m_vec[i]); }
	const double& operator [](int i) const  { return (m_vec[i]); }

	CXVector3D& operator =(const CXVector3D& v)
	{
		m_vec[0] = v.m_vec[0];
		m_vec[1] = v.m_vec[1];
		m_vec[2] = v.m_vec[2];
		return *this;
	}
	CXVector3D& operator *=(double d) 
	{
		m_vec[0] *= d;
		m_vec[1] *= d;
		m_vec[2] *= d;
		return *this;
	}
	CXVector3D& operator /=(double d)
	{
		m_vec[0] /= d;
		m_vec[1] /= d;
		m_vec[2] /= d;
		return *this;
	}
	CXVector3D& operator +=(const CXVector3D& v) 
	{
		m_vec[0] += v.m_vec[0];
		m_vec[1] += v.m_vec[1];
		m_vec[2] += v.m_vec[2];
		return *this;
	}
	CXVector3D& operator -=(const CXVector3D& v) 
	{
		m_vec[0] -= v.m_vec[0];
		m_vec[1] -= v.m_vec[1];
		m_vec[2] -= v.m_vec[2];
		return *this;
	}

	CXVector3D operator -() const { return CXVector3D(-m_vec[0], -m_vec[1], -m_vec[2]); }


	friend CXVector3D operator *(const CXVector3D& v, double d)
	{
		return CXVector3D(	v.m_vec[0] * d,
							v.m_vec[1] * d,
							v.m_vec[2] * d);
	}

	friend CXVector3D operator *(double d, const CXVector3D& v)
	{
		return CXVector3D(	v.m_vec[0] * d,
							v.m_vec[1] * d,
							v.m_vec[2] * d);
	}

	friend CXVector3D operator /(const CXVector3D& v, double d) 
	{
		return CXVector3D(	v.m_vec[0] / d,
							v.m_vec[1] / d,
							v.m_vec[2] / d);
	}

	friend CXVector3D operator +(const CXVector3D& v1, const CXVector3D& v2) 
	{
		return CXVector3D(	v1.m_vec[0] + v2.m_vec[0],
							v1.m_vec[1] + v2.m_vec[1],
							v1.m_vec[2] + v2.m_vec[2]);
	}

	friend CXVector3D operator -(const CXVector3D& v1, const CXVector3D& v2) 
	{
		return CXVector3D(	v1.m_vec[0] - v2.m_vec[0],
							v1.m_vec[1] - v2.m_vec[1],
							v1.m_vec[2] - v2.m_vec[2]);
	}

	friend bool operator ==(const CXVector3D& v1, const CXVector3D& v2) 
	{
		return ((v1.m_vec[0] == v2.m_vec[0]) && (v1.m_vec[1] == v2.m_vec[1]) && (v1.m_vec[2] == v2.m_vec[2]));
	}
	friend bool operator !=(const CXVector3D& v1, const CXVector3D& v2)
	{
		return ((v1.m_vec[0] != v2.m_vec[0]) || (v1.m_vec[1] != v2.m_vec[1]) || (v1.m_vec[2] != v2.m_vec[2]));
	}

private:
	double m_vec[3];
};

#endif // KEVECTOR3D_H
