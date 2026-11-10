#include "xsvgwidget.h"
#include <QPaintEvent>
#include <qsvgrenderer.h>
#include <qpainter.h>
#include <qmenu.h>

CXSvgWidget::CXSvgWidget(QWidget *parent)
	:QSvgWidget(parent)
{
	this->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, &CXSvgWidget::customContextMenuRequested, this, &CXSvgWidget::slotTableMenuRequest);

	m_nKeepAspectRatio = true;
}

CXSvgWidget::~CXSvgWidget()
{

}

void CXSvgWidget::slotTableMenuRequest(const QPoint & point)
{
	QMenu menu;

	if (m_nKeepAspectRatio)
		 menu.addAction("Cancel Aspect Ratio", this, &CXSvgWidget::slotCancelAspectRatio);
	else
		menu.addAction("Keep Aspect Ratio", this, &CXSvgWidget::slotKeepAspectRatio);

	menu.exec(QCursor::pos());
}

void CXSvgWidget::slotCancelAspectRatio()
{
	m_nKeepAspectRatio = false;
	this->update();
}

void CXSvgWidget::slotKeepAspectRatio()
{
	m_nKeepAspectRatio = true;
	this->update();
}

void CXSvgWidget::paintEvent(QPaintEvent *event)
{
	auto pSvgRender = this->renderer();
	if (pSvgRender == nullptr || m_nKeepAspectRatio == false)
	{
		QSvgWidget::paintEvent(event);
		return;
	}

	QPainter painter(this);

	auto size = pSvgRender->defaultSize();
	auto ratio = 1. * size.height() / size.width();

	auto length = qMin(this->width(), this->height());

	int left = this->width() / 2 - length / 2;

	pSvgRender->render(&painter, QRectF(left, 0, length, ratio * length));
}