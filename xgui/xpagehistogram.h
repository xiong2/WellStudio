#ifndef XHISTOGRAMPAGE_H
#define XHISTOGRAMPAGE_H

#include <QWidget>
#include "ui_xhistogram.h"
#include "xhistogram.h"

/*!
 * @class	CXPageHistogram in kepagehistogram.h
 * @brief	The class define a page for object's histogram.
 * @author	pezy
 * @date	2016-11-21
 * @see		CXPageHistogram
 */

class CXPageHistogram : public QWidget
{
	Q_OBJECT
public:
	CXPageHistogram(QWidget *parent, const CXHistogram& histogram);
	~CXPageHistogram();

private:
	void _Init();
	void _InitSlots();

private slots:
	void slotBinChanged();

private:
	Ui_KEPageHistogram m_ui;
	const CXHistogram& m_histogram;
};

#endif // RFHISTOGRAMPAGE_H
