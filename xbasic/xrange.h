#ifndef CXRANGE_H_
#define CXRANGE_H_

#include <QHash>

template <typename T>
struct CXRange
{
	CXRange() : min(), max() {}
	CXRange(const T& min_, const T& max_) : min(min_), max(max_) {}

	template <typename T>
	CXRange(const CXRange<T>& r) : min(r.min), max(r.max) {}
	template <typename T>
	CXRange& operator=(const CXRange<T>& r)
	{
		min = r.min;
		max = r.max;
		return *this;
	}

	template <typename T>
	CXRange(CXRange<T> &&r) noexcept : min(std::move(r.min)), max(std::move(r.max)) {}
	template <typename T>
	CXRange& operator=(CXRange<T> &&r) noexcept
	{
		min = std::move(r.min);
		max = std::move(r.max);
		return *this;
	}

	void swap(CXRange& r) noexcept
	{
		std::swap(min, r.min);
		std::swap(max, r.max);
	}

	T min;
	T max;
};

template <typename T>
inline void swap(CXRange<T>& lhs, CXRange<T>& rhs) noexcept
{
	lhs.swap(rhs);
}

template <typename T>
inline bool operator==(const CXRange<T>& r1, const CXRange<T>& r2)
{
	return r1.min == r2.min && r1.max == r2.max;
}

template <typename T>
inline bool operator!=(const CXRange<T>& r1, const CXRange<T>& r2)
{
	return !(r1 == r2);
}

template <typename T>
inline bool operator<(const CXRange<T>& r1, const CXRange<T>& r2)
{
	return r1.min < r2.min || (r1.min == r2.min && r1.max < r2.max);
}

template <typename T>
inline bool operator>(const CXRange<T>& r1, const CXRange<T>& r2)
{
	return r2 < r1;
}

template <typename T>
inline bool operator<=(const CXRange<T>& r1, const CXRange<T>& r2)
{
	return !(r2 < r1);
}

template <typename T>
inline bool operator>=(const CXRange<T>& r1, const CXRange<T>& r2)
{
	return !(r1 < r2);
}

template <typename T>
inline CXRange<T> keMakeRange(const T& x, const T& y)
{
	return CXRange<T>(x, y);
}

template <typename T>
inline uint qHash(const CXRange<T>& r, uint seed)
{
	return qHash(qMakePair<T, T>(r.min, r.max));
}

#endif // CXRANGE_H_
