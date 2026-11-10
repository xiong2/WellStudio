#ifndef XDRAWHISTOGRAM_H
#define XDRAWHISTOGRAM_H

#include <QFrame>
#include "xhistogram.h"

/*!
 * @class	CXDrawHistogram in kedrawhistogram.h
 * @brief	The class define a frame of histogram.
 * @author	pezy
 * @date	2016-11-21
 * @see		
 */

class CXObject;
class CXAxis;

class CXDrawHistogram : public QFrame
{
	Q_OBJECT
public:
	explicit CXDrawHistogram(QWidget *parent);
	~CXDrawHistogram();

	void SetHistogram(const CXHistogram& histogram);

public slots:
	void slotSetInterval(const QString& strInterval);
	void slotSetNum(const QString& strNum);
	void slotYRepresentationChanged(int iIndex);

protected:
	virtual void paintEvent(QPaintEvent *);
	virtual void wheelEvent(QWheelEvent *);

private:
	void _DrawXAxis(QPainter *painter, QRect rect);
	void _DrawYAxis(QPainter *painter, QRect rect);
	void _DrawHistogram(QPainter *painter, QRect rect);
	void _DrawAnnotation(QPainter *painter, QRect rect);
	double _GetSecondMaxValue(const vector<double>& vec);
	void _CalcBins();

private:	
	CXAxis *m_pAxisX = nullptr;
	CXAxis *m_pAxisY = nullptr;
	QRect m_rect;

	double m_dBinWidth = 0.0;
	std::vector<double> m_vecX, m_vecY;
	bool m_bYNumber = false;

	CXHistogram m_histogram;
};

#endif // KEDRAWHISTOGRAM_H
