#include "x2dsectionview.h"

#include <QOpenGLWidget>
#include <QResizeEvent>
#include <QScrollBar>

#include "x2dsectionwindow.h"
#include "xglobal.h"
#include "x2dsectionaxis.h"
#include "xbaseconsole.h"
#include "xeventconsole.h"
#include "xfaultsticks.h"
#include "xsectionlinemode.h"
#include "xtimesliceitem.h"
#include "xsectionscene.h"

CX2DSectionView::CX2DSectionView(QGraphicsScene* scene, EXWindowType eWindowType, QWidget* parent)
	: CXGraphicsView(scene, eWindowType, parent), m_pMainWindow(nullptr)
	, m_pDigitizingItem(nullptr)
	, m_pSectionLineItem(nullptr), m_pSectionTimeSlice(nullptr)
{
	setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	setFrameShadow(Raised);
	setAlignment(Qt::AlignLeft | Qt::AlignTop);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	setFrameShadow(QFrame::Raised);

 	m_pScene = dynamic_cast<CXSectionScene *>(scene);
	m_pMainWindow = dynamic_cast<CX2DSectionWindow*>(scene->parent());

	_InitGLWidget();
}

CX2DSectionView::~CX2DSectionView()
{

}

void CX2DSectionView::_InitGLWidget()
{
    m_pGLWidget = new QOpenGLWidget;
	QSurfaceFormat format;
	format.setSamples(8);
	m_pGLWidget->setFormat(format);
	m_pGLWidget->setMouseTracking(true);
	setViewport(m_pGLWidget);
}

QOpenGLWidget *CX2DSectionView::GetGLWidget() const
{
	return m_pGLWidget;
}

void CX2DSectionView::resizeEvent(QResizeEvent* event)
{
	// handle resize event manually
	// Viewer size may be changed according to top or left margins change.
	// It will cause scroll bars to change accordingly.
	m_pMainWindow->ChangeViewerSize();

	return;
}

void CX2DSectionView::mousePressEvent(QMouseEvent* event)
{
	m_pScene->HandleMouseEvent(event, eSecButtonPress);
}

void CX2DSectionView::mouseReleaseEvent(QMouseEvent* event)
{
	m_pScene->HandleMouseEvent(event, eSecButtonRelease);
}

void CX2DSectionView::mouseMoveEvent(QMouseEvent *event)
{
	m_pScene->ShowPositionInfo(event);
	m_pScene->HandleMouseEvent(event, eSecMouseMove);
}

void CX2DSectionView::mouseDoubleClickEvent(QMouseEvent* event)
{
	m_pScene->HandleMouseEvent(event, eSecDoubleClick);
}