#ifndef XWIDGET3DSURFACE_H
#define XWIDGET3DSURFACE_H

#include <qwidget.h>
#include "xguiplus_global.h"
#include <qmap.h>
#include "ui_xwidget3dsurface.h"

#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QHeightMapSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>

using namespace QtDataVisualization;

/**
*	@class	 CXWidget3DSurface in the file "kewidget3dsurface.h"
*	@brief	 The class provide a widget for rendering 3-D surface
*	@author	Yong Shu
*	@date	 11/2/2016
*/

class XGUIPLUS_EXPORT CXWidget3DSurface : public QWidget
{
	Q_OBJECT
public:
	CXWidget3DSurface(const QString& strWidgetName = "", QWidget* parent=nullptr);
	~CXWidget3DSurface();

	void ADDOneSurface(int iIndex, float* pData, int m, int n);

	void Update(int iIndex, float* pData, int m, int n);

	void SetVisibility(int iIndex, bool bShow);

	void SetPolar(bool bPolar);

private slots:
	void slotChangeColormap(const QString& strColormapName);

private:
	void _Init();
	void _SetAxis(float * pData, int nPointNum);
	QSurfaceDataArray* _GenerateData(float * pData, int m, int n);
	void _ChangeColormap(const QString& strColormapName);

private:
	QtDataVisualization::Q3DSurface *m_graph;
	QMap<int, QSurface3DSeries*> m_mapDataSeries;
	float m_xmin, m_xmax, m_ymin, m_ymax, m_zmin, m_zmax;
	float m_xcoodmin, m_xcoodmax, m_ycoodmin, m_ycoodmax, m_zcoodmin, m_zcoodmax;

private:
	Ui::Widget3DSurface m_ui;
	
};

#endif // KEWIDGET3DSURFACE_H
