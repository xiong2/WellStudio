#include "xtimesliceitem.h"
#include "xseismicsection.h"
#include "x2daxishelper.h"
#include "xscene.h"
#include "xviewinfotimeslice.h"
#include "xeventconsole.h"
#include "xsectionscene.h"
#include "xcoordtransformer.h"

CXTimeSliceItem::CXTimeSliceItem(CX2DSectionWindow *pWindow,QGraphicsItem *parent):CXAbstractItem(pWindow,parent)
{
	m_Path = QPainterPath();
	m_Pen = QPen();
}


CXTimeSliceItem::~CXTimeSliceItem(void)
{
}

void CXTimeSliceItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
	 CXViewInfoTimeSlice *pSliceViewInfo = dynamic_cast<CXViewInfoTimeSlice*>(m_pViewInfo);
	 if (!pSliceViewInfo)
		 return;

	 CXSectionScene* pScene = dynamic_cast<CXSectionScene*>(scene());
	 if (!pScene)
		 return;

	 CXCoordTransformer transformer(pScene);

	painter->save();
	m_Pen.setStyle((Qt::PenStyle)pSliceViewInfo->GetLineStyle());
	m_Pen.setWidth(pSliceViewInfo->GetLineSize());
	m_Pen.setColor(pSliceViewInfo->GetLineColor());
	painter->setPen(m_Pen);

	m_Path = QPainterPath();

	double scenex, sceney;
	transformer.Ratio2Scene(0, m_dZRatio, scenex, sceney);
	m_Path.moveTo((int)scenex, (int)sceney);

	transformer.Ratio2Scene(1, m_dZRatio, scenex, sceney);
	m_Path.lineTo((int)scenex, (int)sceney);

	painter->drawPath(m_Path);
	painter->restore();
}

QRectF CXTimeSliceItem::boundingRect() const
{
	return _CalcDrawPathBoundingRect(m_Path,m_Pen);
}

QPainterPath  CXTimeSliceItem::shape() const 
{
	return _CalcShapeFromPath(m_Path,m_Pen);
}

void CXTimeSliceItem::_UpdateData()
{
	CXSeismicSection* pSection = dynamic_cast<CXSeismicSection*>(GetItemObject());
	if (!pSection)
		return ;

	CXSectionScene* pScene = dynamic_cast<CXSectionScene*>(scene());
	if (!pScene)
		return;

	CXCoordTransformer transformer(pScene);

	double dZ = pSection->GetSectionNumber();

	double scenex, sceney, ratiox, ratioy;
	transformer.World2Scene(1., dZ, scenex, sceney);
	transformer.Scene2Ratio(scenex, sceney, ratiox, ratioy);

	m_dZRatio = ratioy;
}

void CXTimeSliceItem::SynSectionNumber(QPointF pos)
{
	CXSeismicSection	*pSection = dynamic_cast<CXSeismicSection*>(GetItemObject());
	if (!pSection)
		return;

	CXSectionScene* pScene = dynamic_cast<CXSectionScene*>(scene());
	if (!pScene)
		return;

	CXCoordTransformer transformer(pScene);

	double worldx, worldy;
	transformer.View2World(pos.x(), pos.y(), worldx, worldy);

	double dLineNumber = worldy;
	
	CXProcessEvent processEvent;
	pSection->SetSectionNumber(dLineNumber);
	pSection->AddEvent(EDataChanged);
}
