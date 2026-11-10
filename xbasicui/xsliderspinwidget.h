#ifndef XSLIDERSPINWIDGET_H
#define XSLIDERSPINWIDGET_H

#include "xsliderex.h"

class QLabel ;
class QDoubleSpinBox ;

class CXFilterEventSlider : public CXSliderEx
{
	Q_OBJECT

public:
	CXFilterEventSlider(QWidget * parent = 0) : CXSliderEx(parent){}
	~CXFilterEventSlider() {}

signals:
	void CurrentValueChanged(int);
	void SliderReleased();

protected:
	virtual void mouseMoveEvent(QMouseEvent *) override;
	virtual void mousePressEvent(QMouseEvent *) override;
	virtual void mouseReleaseEvent(QMouseEvent *) override;
};

class XBASICUI_EXPORT CXSliderSpinWidget : public QWidget
{
	Q_OBJECT

public:
	CXSliderSpinWidget(QWidget* parent = 0);
	~CXSliderSpinWidget() {}

	void InitWidget(double dStart, double dEnd, double dStep, int nCount, int nDecimal);

	double GetValue();
	void SetValue(double dValue);

	int GetCurrentIndex();
	void SetCurrentIndex(int nIndex);

	int GetRangeMinValue();
	int GetRangeMaxValue();

	void SetLabelString(const QString& str);
	void SetEnabled(bool bEnabled);
	void HideLabel(bool bHidden);
	void SetSpinSingleStep(double dStep);

signals:
	void ValueChanged(double);
	void SliderReleased();
	void EditingFinished();

private slots:
	void slotSliderValueChanged(int);
	void slotSpinValueChanged(double);
	void slotEditingFinished();

private:
	void _BlockSignals(bool bBlock);
	void _SetSpinBoxValue(double dValue);

	QLabel* m_pLblString;
	CXFilterEventSlider* m_pSlider;
	QDoubleSpinBox* m_pSpin;
	int m_nDecimal;
};

/*==============================================================================
	CXRangeComponent
										 ______________
	start: -|-------------------------- |_start_number_|
	end:   --------------------------|- |__end_number__|

==============================================================================*/

class XBASICUI_EXPORT CXRangeComponent : public QWidget
{
	Q_OBJECT

public:
	CXRangeComponent(QWidget* parent = 0, bool bEmitOnlyReleaseMouse = false, bool bStartEqualToEnd = false);
	~CXRangeComponent(){}

	void InitComponent(double dRangeStart, double dRangeEnd, double dStep, int nCount, double dStartValue, double dEndValue);

	void SetComponentLabel(const QString& strStratLabel, const QString& strEndLabel);
	void SetLockRange(bool bLockRange);
	void ResetRange();

	double GetStartValue() const { return m_pStartWidget->GetValue(); }
	double GetEndValue() const { return m_pEndWidget->GetValue(); }

	void EmitOnlyReleaseMouse(bool bEmitOnlyReleaseMouse) { m_bEmitOnlyReleaseMouse = bEmitOnlyReleaseMouse; }

signals:
	void ValueChanged(double dStartValue, double dEndValue);

private slots:
	void slotStartValueChanged(double);
	void slotEndValueChanged(double);
	void slotValueChanged();

private:
	void _BlockSignals(bool bBlock);

	QLabel* m_pStartLabel;
	CXSliderSpinWidget* m_pStartWidget;

	QLabel* m_pEndLabel;
	CXSliderSpinWidget* m_pEndWidget;

	int m_nLockedRangeValue;
	bool m_bLockRange;
	bool m_bStartEqualToEnd;
	bool m_bEmitOnlyReleaseMouse;
};

#endif // KESLIDERSPINWIDGET_H
