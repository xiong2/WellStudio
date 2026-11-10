#pragma once
#include "xbasic_global.h"
#include <array>
#include <numeric>

struct XBASIC_EXPORT XPoint
{
	XPoint() = default;
	XPoint(double xx, double yy, double zz) : x(xx), y(yy), z(zz) {}

	double x;
	double y;
	double z;

	friend bool operator==(const XPoint& lhs, const XPoint& rhs)
	{
		double dTol = 1e-6;
		
		double dx = rhs.x - lhs.x;
		double dy = rhs.y - lhs.y;
		double dz = rhs.z - lhs.z;

		return (dx * dx + dy * dy + dz * dz) < dTol * dTol;
	}
};

struct XBASIC_EXPORT XPointHashFunc
{
	size_t operator()(const XPoint& p) const
	{
		size_t hx = std::hash<double>()(p.x);
		size_t hy = std::hash<double>()(p.y);
		size_t hz = std::hash<double>()(p.z);
		return (hx ^ (hy << 1)) ^ hz;
	}
};

template <typename T, size_t Dimensions>
class XVec
{
public:
	XVec() : m_array{} {}

    T& operator[](size_t i) { return m_array[i]; }
    T operator[](size_t i) const { return m_array[i]; }

	bool IsNull() const { return m_array == std::array<T, Dimensions>{}; }

    friend T operator*(const XVec& v1, const XVec& v2)
    {
        return std::inner_product(v1.m_array.cbegin(), v1.m_array.cend(), v2.m_array.cbegin(), T());
    }
    friend bool operator==(const XVec& v1, const XVec& v2)
    {
        return v1.m_array == v2.m_array;
    }
    friend XVec operator+(const XVec& v1, const XVec& v2)
    {
        XVec sum(v1);
        sum += v2;
        return sum;
    }
    friend XVec operator-(const XVec& v1, const XVec& v2)
    {
        XVec minuend(v1);
        minuend -= v2;
        return minuend;
    }
    friend XVec operator*(const XVec& lhs, T rhs)
    {
        XVec ret(lhs);
        ret *= rhs;
        return ret;
    }

    XVec operator-() const
    {
        XVec negative(*this);
        std::for_each(negative.m_array.begin(), negative.m_array.end(), [](T& v) { v = -v; });
        return negative;
    }

    // scale
    void operator*=(T rhs)
    {
        std::for_each(m_array.begin(), m_array.end(), [rhs](T& v) { v *= rhs; });
    }

    void operator/=(T rhs)
    {
        std::for_each(m_array.begin(), m_array.end(), [rhs](T& v) { v /= rhs; });
    }

    void operator+=(const XVec& rhs)
    {
        for (int i = 0; i != Dimensions; ++i)
            m_array[i] += rhs[i];
    }

    void operator-=(const XVec& rhs)
    {
        for (int i = 0; i != Dimensions; ++i)
            m_array[i] -= rhs[i];
    }

    T LengthSquared() const
    {
        T sum = T();
        for (size_t i = 0; i != Dimensions; ++i)
        {
            sum += m_array[i] * m_array[i];
        }
        return sum;
    }

    T Length() const
    {
        T lenSquared = LengthSquared();
        return std::sqrt(lenSquared);
    }

    void Normalize()
    {
        T len         = Length();
        double factor = len == 0 ? 0.0 : 1.0 / len;

        *this *= factor;
    }

    XVec Normalized() const
    {
        XVec norm(*this);
        norm.Normalize();
        return norm;
    }

protected:
    std::array<T, Dimensions> m_array;
};

template <typename T>
class XVec2 : public XVec<T, 2>
{
public:
    XVec2() = default;
    XVec2(T x, T y)
    {
        m_array[0] = x;
        m_array[1] = y;
    }
    XVec2(const XVec<T, 2>& p)
    {
		for (size_t i = 0; i != 2; ++i)
		{
			m_array[i] = p[i];
		}
    }

	bool operator<(const XVec2& other) const
	{
		if (m_array[0] < other.m_array[0])
			return true;
		else if (m_array[0] == other.m_array[0])
			return m_array[1] < other.m_array[1];
		else
			return false;
	}

    T x() const { return m_array[0]; }
    T y() const { return m_array[1]; }

    T& rx() { return m_array[0]; }
    T& ry() { return m_array[1]; }

    XVec2 Perpendicular() const
    {
        return XVec2(m_array[1], -m_array[0]);
    }
};

template <typename T>
class XVec3 : public XVec<T, 3>
{
public:
    XVec3() = default;
    XVec3(T x, T y, T z)
    {
        m_array[0] = x;
        m_array[1] = y;
        m_array[2] = z;
    }
	XVec3(XPoint p)
	{
		m_array[0] = p.x;
		m_array[1] = p.y;
		m_array[2] = p.z;
	}
    XVec3(const XVec<T, 3>& p)
    {
		for (size_t i = 0; i != 3; ++i)
		{
			m_array[i] = p[i];
		}
    }

    T x() const { return m_array[0]; }
    T y() const { return m_array[1]; }
    T z() const { return m_array[2]; }

    T& rx() { return m_array[0]; }
    T& ry() { return m_array[1]; }
    T& rz() { return m_array[2]; }

    // cross product
    XVec3 operator^(const XVec3& rhs) const
    {
        return XVec3(m_array[1] * rhs.m_array[2] - m_array[2] * rhs.m_array[1],
            m_array[2] * rhs.m_array[0] - m_array[0] * rhs.m_array[2],
            m_array[0] * rhs.m_array[1] - m_array[1] * rhs.m_array[0]);
    }
	
	XVec2<T> ToVec2() const
	{
		return XVec2<T>(m_array[0], m_array[1]);
	}

	XPoint ToPoint() const
	{
		return XPoint(m_array[0], m_array[1], m_array[2]);
	}
};

typedef XBASIC_EXPORT XVec2<double> XVec2d;
typedef XBASIC_EXPORT XVec3<double> XVec3d;

template <typename T, size_t Dimensions>
struct XBASIC_EXPORT XSegment
{
	XVec<T, Dimensions> p0;
	XVec<T, Dimensions> p1;
};