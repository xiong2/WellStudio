#ifndef XSLIDERCOMPLEX_H
#define XSLIDERCOMPLEX_H

#include <QWidget>
#include "xbasicui_global.h"
#include "ui_xsliderwidget.h"

class XBASICUI_EXPORT CXSliderComplex : public QWidget
{
	Q_OBJECT

public:
	CXSliderComplex(QWidget *parent=NULL);
	~CXSliderComplex();

	///@brief Set data range and precision
	void SetRangeAndPrecision(double dMin, double dMax, double dStep, int nPrecision = 0);

	///@brief Set slider name
	void SetSliderName(const QString& strName);

	///@brief Get the min and max values
	double GetMinValue();
	double GetMaxValue();

	///@brief Set the min and max position
	void SetMinPosition(double dMin);
	void SetMaxPosition(double dMax);

	void SetNameVisible(bool bVisible);

signals:
    void SliderReleased();

private slots:
	void slotChangeMin();
	void slotChangeMax();
	void slotMinValueChanged(int);
	void slotMaxValueChanged(int);

private:
	Ui::WidgetSliderComplex m_ui;

	int m_nPrecision;

	double m_dDataMin, m_dDataMax, m_dStep;

	int m_nTotalNum;
	
};

#endif // KESLIDERCOMPLEX_H
