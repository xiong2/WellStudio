#include "xrandomlineitem.h"
#include "xsectionscene.h"
#include "xseismicsection.h"
#include "xseismicrandomsection.h"
#include "xcoordtransformer.h"
#include <cassert>

CXRandomLineItem::CXRandomLineItem(CX2DSectionWindow *pWindow, QGraphicsItem *parent) :CXAbstractItem(pWindow)
{
	setZValue(3);
	m_nLineWidth = 2;
}


CXRandomLineItem::~CXRandomLineItem(void)
{
}

QRectF CXRandomLineItem::boundingRect() const
{
	if (!scene())
		return QRectF();

	
	double xmin, ymin, xmax, ymax;

	CXSectionScene* pScene = dynamic_cast<CXSectionScene*>(scene());
	CXCoordTransformer transformer(pScene);

	transformer.Ratio2Scene(0, 0, xmin, ymin);
	transformer.Ratio2Scene(1, 1, xmax, ymax);

	return QRectF(QPointF(xmin - m_nLineWidth, ymin - m_nLineWidth), QPointF(xmax + m_nLineWidth, ymax + m_nLineWidth));
}

void CXRandomLineItem::_UpdateData()
{
	CXSeismicRandomSection* pSection = static_cast<CXSeismicRandomSection*>(GetItemObject());
	assert(pSection);

	int nTraceNum = pSection->GetTraceNum();
	vector<int> vecKeyIndex = pSection->GetVecTPIndex();

	m_vecDataRatio.resize(vecKeyIndex.size());

	for (int i = 0; i < m_vecDataRatio.size(); ++i)
	{
		m_vecDataRatio[i] = vecKeyIndex[i]*1. / (nTraceNum-1.);
	}
}

void CXRandomLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	CXSectionScene* pScene = dynamic_cast<CXSectionScene*>(scene());
	if (!pScene)
		return;	

	painter->save();

	painter->setRenderHint(QPainter::Antialiasing, true);

	QPen pen;
	pen.setWidth(m_nLineWidth);
	pen.setColor(Qt::black);
	painter->setPen(pen);

	CXCoordTransformer transformer(pScene);
	double scenex, sceney;

	QPainterPath path;
	for (int i = 0; i < m_vecDataRatio.size(); ++i)
	{
		transformer.Ratio2Scene(m_vecDataRatio[i], 0, scenex, sceney);

		path.moveTo((int)scenex, (int)sceney);

		transformer.Ratio2Scene(m_vecDataRatio[i], 1, scenex, sceney);
		path.lineTo((int)scenex, (int)sceney);
	}

	painter->drawPath(path);	

	painter->restore();
}
