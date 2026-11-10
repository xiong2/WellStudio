#ifndef XDOUBLESPINBOXEX_H
#define XDOUBLESPINBOXEX_H

#include <QDoubleSpinBox>

/*!
 *	@brief	custom double spin box for negative step
 *	@author	pezy
 *	@date	2015-09-24
 */

class CXDoubleSpinBoxEx : public QDoubleSpinBox
{
	Q_OBJECT

public:
	CXDoubleSpinBoxEx(QWidget *parent) : QDoubleSpinBox(parent) {}
	~CXDoubleSpinBoxEx() {}

	void Init(double dStart, double dEnd, double dStep, int nCount);
	double GetCurValue() const;
	void SetValue(double dValue);

	virtual QString	textFromValue(double dValue) const override;

private:
	double m_dStep = 1.0;
	double m_dStart = 0.0;
	double m_dEnd = 1.0;
};

class CXSpinBoxEx : public QSpinBox
{
	Q_OBJECT

public:
	CXSpinBoxEx(QWidget *parent) : QSpinBox(parent) {}
	~CXSpinBoxEx() {}

	void Init(int iStart, int iEnd, int iStep, int nCount);
	int GetCurValue() const;
	void SetValue(int value);

	virtual QString	textFromValue(int value) const override;

private:
	int m_iStep = 1;
	int m_iStart = 0;
	int m_iEnd = 1;
};

#endif // KEDOUBLESPINBOXEX_H
