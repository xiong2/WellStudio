#include "xwidget3dsurface.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtGui/QScreen>
#include <QVector3D>
#include <qmenu.h>
#include "xmathmacro.h"
#include "xcolormap.h"


CXWidget3DSurface::CXWidget3DSurface(const QString& strWidgetName, QWidget* parent)
	:QWidget(parent)
{
	m_ui.setupUi(this);

	setAttribute(Qt::WA_DeleteOnClose);
	setWindowTitle(strWidgetName);

	_Init();	

	connect(m_ui.m_pColormapWidget, &CXColormapWidget::signalChangedColormap, this, &CXWidget3DSurface::slotChangeColormap);
	m_ui.m_pColormapWidget->SetColormapName("rainbow");

	m_xmin = m_ymin = m_zmin = M_FLT_MAX;
	m_xmax = m_ymax = m_zmax = M_FLT_NEGATIVEMAX;
}

CXWidget3DSurface::~CXWidget3DSurface()
{
	delete m_graph;
}

void CXWidget3DSurface::slotChangeColormap(const QString& strColormapName)
{
	_ChangeColormap(strColormapName);
}

void CXWidget3DSurface::_ChangeColormap(const QString& strColormapName)
{
	QString strName = strColormapName;

	if (strName.isEmpty())
		strName = m_ui.m_pColormapWidget->GetColormapName();		

	m_ui.m_pColormapWidget->SetDisplayRange(m_ymin, m_ymax);

	CXColormap* pColormap = CXColormap::GetColormap(strName);
	if (!pColormap)
		return;

	int nColorNum = pColormap->GetColorNum();

	QLinearGradient gr;
	for (int i = 0; i < nColorNum; ++i)
	{
		gr.setColorAt(i*1.0 / (nColorNum - 1), pColormap->GetColorAt(i));
	}

	for (auto series : m_graph->seriesList())
	{
		series->setBaseGradient(gr);
		series->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
	}
}

void CXWidget3DSurface::_Init()
{
	m_graph = new Q3DSurface();
	QWidget *container = QWidget::createWindowContainer(m_graph);
	m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);	

	//QSize screenSize = m_graph->screen()->size();
	//container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.6));
	//container->setMaximumSize(screenSize);
	//container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	container->setFocusPolicy(Qt::StrongFocus);

	m_ui.m_pScrollArea->setWidget(container);

	// axis
	m_graph->setAxisX(new QValue3DAxis);
	m_graph->setAxisY(new QValue3DAxis);
	m_graph->setAxisZ(new QValue3DAxis);
}

void CXWidget3DSurface::_SetAxis(float * pData, int nPointNum)
{
	// X->Z, Y->X, Z->Y
	for (int i = 0; i < nPointNum; ++i)
	{
		m_xmin = qMin(m_xmin, pData[3 * i + 1]);
		m_xmax = qMax(m_xmax, pData[3 * i + 1]);

		m_ymin = qMin(m_ymin, pData[3 * i + 2]);
		m_ymax = qMax(m_ymax, pData[3 * i + 2]);

		m_zmin = qMin(m_zmin, pData[3 * i]);
		m_zmax = qMax(m_zmax, pData[3 * i]);
	}

	if (m_graph->isPolar())
	{
		m_xcoodmin = m_zmin;
		m_xcoodmax = m_zmax;
		m_zcoodmin = m_zmin;
		m_zcoodmax = m_zmax;

		m_ycoodmin = m_ymin - 0.1*(m_ymax - m_ymin);
		m_ycoodmax = m_ymax + 0.1*(m_ymax - m_ymin);

		//m_graph->axisX()->setRange(m_xcoodmin, m_xcoodmax);
		m_graph->axisY()->setRange(m_ycoodmin, m_ycoodmax);
		//m_graph->axisZ()->setRange(m_zcoodmin, m_zcoodmax);
	}
	else
	{
		m_xcoodmin = floorf(m_xmin);
		m_xcoodmax = ceilf(m_xmax);
		m_zcoodmin = floorf(m_zmin);
		m_zcoodmax = ceilf(m_zmax);
		m_ycoodmin = floorf(m_ymin);
		m_ycoodmax = ceilf(m_ymax);

		m_graph->axisX()->setRange(m_xcoodmin, m_xcoodmax);
		m_graph->axisY()->setRange(m_ycoodmin, m_ycoodmax);
		m_graph->axisZ()->setRange(m_zcoodmin, m_zcoodmax);
	}



	// set axis
	m_graph->axisX()->setLabelFormat("%.2f");
	m_graph->axisZ()->setLabelFormat("%.2f");


	if (m_mapDataSeries.isEmpty())
	{
		m_graph->axisX()->setLabelAutoRotation(30);
		m_graph->axisY()->setLabelAutoRotation(90);
		m_graph->axisZ()->setLabelAutoRotation(30);
	}
}

QSurfaceDataArray* CXWidget3DSurface::_GenerateData(float * pData, int m, int n)
{
	// X->Znew, Y->Xnew, Z->Ynew
	// set data
	//				Z					Ynew		
	//				|					 | 	
	//				|______Y    =>		 |_____Xnew	
	//				/                    /
	//			   /                    /
	//			  X 	               Znew
	QSurfaceDataArray *dataArray = new QSurfaceDataArray;
	dataArray->reserve(m);
	for (int i = 0; i < m; ++i)
	{
		// Znew
		QSurfaceDataRow *newRow = new QSurfaceDataRow(n);
		float znew = pData[i*n * 3];
		int index = 0;
		for (int j = 0; j < n; ++j)
		{
			float xnew = pData[i*n * 3 + j * 3 + 1];
			float ynew = pData[i*n * 3 + j * 3 + 2];
			(*newRow)[index++].setPosition(QVector3D(xnew, ynew, znew));
		}
		*dataArray << newRow;
	}
	return dataArray;
}

void CXWidget3DSurface::ADDOneSurface(int iIndex, float * pData, int m, int n)
{
	// set axis
	_SetAxis(pData, m*n);

	if (m_mapDataSeries.contains(iIndex))
	{
		Update(iIndex, pData, m, n);

		QList<QSurface3DSeries*> listSeries = m_graph->seriesList();
		if (!listSeries.contains(m_mapDataSeries.value(iIndex)))
			m_graph->addSeries(m_mapDataSeries.value(iIndex));

		return;
	}

	QSurfaceDataArray *dataArray = _GenerateData(pData, m, n);

	QSurfaceDataProxy* pProxy = new QSurfaceDataProxy();
	QSurface3DSeries* p3DSeries = new QSurface3DSeries(pProxy);
	pProxy->resetArray(dataArray);

	m_mapDataSeries.insert(iIndex, p3DSeries);

	// draw
	p3DSeries->setDrawMode(QSurface3DSeries::DrawSurface);
	p3DSeries->setFlatShadingEnabled(true);	
	m_graph->addSeries(p3DSeries);

	_ChangeColormap("");
}

void CXWidget3DSurface::Update(int iIndex, float * pData, int m, int n)
{
	QSurface3DSeries* p3DSeries = m_mapDataSeries.value(iIndex, NULL);
	if (!p3DSeries)
		return;

	QSurfaceDataArray *dataArray = _GenerateData(pData, m, n);
	if (!dataArray)
		return;

	p3DSeries->dataProxy()->resetArray(dataArray);
}

void CXWidget3DSurface::SetVisibility(int iIndex, bool bShow)
{
	if (!m_mapDataSeries.contains(iIndex))
		return;

	if (bShow)
		m_graph->addSeries(m_mapDataSeries.value(iIndex));
	else
		m_graph->removeSeries(m_mapDataSeries.value(iIndex));
}

void CXWidget3DSurface::SetPolar(bool bPolar)
{
	m_graph->setPolar(bPolar);
}

