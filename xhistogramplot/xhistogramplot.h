#ifndef CXHistogramPlot_H
#define CXHistogramPlot_H

#include "xhistogramplot_global.h"
#include "xwindow.h"

class QUuid;

class XHISTOGRAMPLOT_EXPORT CXHistogramPlot : public CXWindow
{
public:
	CXHistogramPlot(QString sWindowName, QWidget *parent = 0, Qt::WindowFlags f = Qt::Window);
	~CXHistogramPlot();

	virtual CXScene* GetScene() override;
	virtual void InitWindow();

private slots:
	void slotSetting();

protected:
	virtual void itemChanged(bool bAdd, QUuid objectID) override;
};

#endif // RLHISTOGRAMPLOT_H
