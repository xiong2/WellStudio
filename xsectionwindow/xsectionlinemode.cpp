#include "xsectionlinemode.h"

#include "xseismicsection.h"
#include "xscene.h"
#include "xseismicrandomsection.h"
#include "xeventconsole.h"
#include "x2daxishelper.h"

CXSectionLineMode::CXSectionLineMode(CX2DSectionWindow *pWindow, QGraphicsItem *parent) : QObject(),CXAbstractItem(pWindow, parent)
{
	m_Pen = QPen(); 
}


CXSectionLineMode::~CXSectionLineMode(void)
{
}

void CXSectionLineMode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
	painter->save();
	m_Pen.setWidth(3);
	m_Pen.setColor(Qt::black);
	painter->setPen(m_Pen);
	painter->drawPath(m_Path);
	painter->restore();
}

QRectF CXSectionLineMode::boundingRect() const
{
	return _CalcDrawPathBoundingRect(m_Path,m_Pen); 
}

QPainterPath  CXSectionLineMode::shape() const 
{
	return _CalcShapeFromPath(m_Path,m_Pen);
}

void CXSectionLineMode::_UpdateData()
{	
	m_Path = QPainterPath() ;
	CX2DAxisHelper *pXAxis = m_pSectionWindow->GetAxisWidget()->GetXAxis();
	if (pXAxis == NULL)
	{
		return;
	}
	QRectF rect =m_pSectionWindow->GetScene()->sceneRect();
	CXObject	*pCurSection = m_pSectionWindow->GetCurrentGeometryObj();//Background section .
	int iRandomLineNum (-1);
	EXObjectType eNeedDisType = GetItemObject()->GetObjectType();
	if (eNeedDisType == EXRandomSection)
	{
		CXSeismicRandomSection *pRandomSection = dynamic_cast<CXSeismicRandomSection*>(GetItemObject());
		vector<int> vecInline, vecXline;
		pRandomSection->GetLineNumbers(vecInline, vecXline);
		int iLineNumber = vecInline.size();
		if (pCurSection->GetObjectType() == eNeedDisType)
		{
			return;
		}
		CXSeismicSection	*pSection =  dynamic_cast<CXSeismicSection*>(pCurSection);
		EXSectionType eType = pSection->GetSectionType();
		int iSectionNumber = pSection->GetSectionNumber();
		for (int i = 0 ; i < iLineNumber; ++i)
		{
			if (eType == eInlineSection)
			{
				iRandomLineNum =vecInline[i];
			}
			else if (eType == eCrosslineSection)
			{
				iRandomLineNum =vecXline[i];
			}
			else
			{
				continue;
			}
			if (iSectionNumber == iRandomLineNum)
			{
				double dBegin,dEnd;
				pXAxis->GetAxisRange(dBegin,dEnd);
				int iPosX = 1;// pXAxis->MapDataToScene(i + dBegin);
				m_Path.moveTo(iPosX,rect.top());
				m_Path.lineTo(iPosX,rect.bottom());
			}
		}
	}
	else if (eNeedDisType== EXSeismicSection)
	{
		if (pCurSection->GetObjectType() == EXSeismicSection)//back ground is seismic section
		{	
			CXSeismicSection *pSection =  dynamic_cast<CXSeismicSection*>(pCurSection);	
			CXSeismicSection *pNeedDisSection = dynamic_cast<CXSeismicSection*>(GetItemObject());
			if(pSection->GetSectionType() == pNeedDisSection->GetSectionType())
			{
				return;
			}
			else
			{
				double dSecNum = pNeedDisSection->GetSectionNumber();
				int nPos = 1;// pXAxis->MapDataToScene(dSecNum);
				m_Path.moveTo(nPos,rect.top());
				m_Path.lineTo(nPos,rect.bottom());
			}
		}
		else if (pCurSection->GetObjectType() == EXRandomSection)// //back ground is Random Section
		{
			CXSeismicRandomSection *pRandomSection = dynamic_cast<CXSeismicRandomSection*>(pCurSection);
			vector<int> vecInline, vecXline;
			pRandomSection->GetLineNumbers(vecInline, vecXline);
			int iLineNumber = vecInline.size();
			CXSeismicSection *pNeedDisSection = dynamic_cast<CXSeismicSection*>(GetItemObject());
			EXSectionType eNeedDisType = pNeedDisSection->GetSectionType();
			int iSectionNumber = pNeedDisSection->GetSectionNumber();
			for (int i = 0 ; i < iLineNumber; ++i)
			{
				if (eNeedDisType == eInlineSection)
				{
					iRandomLineNum =vecInline[i];
				}
				else if (eNeedDisType == eCrosslineSection)
				{
					iRandomLineNum =vecXline[i];
				}
				else
				{
					continue;
				}
				if (iSectionNumber == iRandomLineNum)
				{
					double dBegin,dEnd;
					pXAxis->GetAxisRange(dBegin,dEnd);
					int iPosX = 1;// pXAxis->MapDataToScene(i + dBegin);
					m_Path.moveTo(iPosX,rect.top());
					m_Path.lineTo(iPosX,rect.bottom());
				}
			}
		}
		else
		{

		}
	}
	else
	{

	}
}

void CXSectionLineMode::slotSceneChanged()
{
	this->_UpdateData();
	QGraphicsItem::update();
}

void CXSectionLineMode::SynSectionNumber(QPointF pos)
{
	CXSeismicSection* pSection = dynamic_cast<CXSeismicSection*>(GetItemObject());
	if (!pSection) return;
	QMargins marjins;// = m_pSectionWindow->GetMargins();
	double dBegin, dEnd;
	double nLineNumber;

	CX2DAxisHelper* pXAxis = m_pSectionWindow->GetAxisWidget()->GetXAxis();
	pXAxis->GetAxisRange(dBegin, dEnd);
	nLineNumber = 1;// pXAxis->MapSceneToData(pos.x() + marjins.left());
	if (nLineNumber < dBegin || nLineNumber > dEnd)
	{
		return;
	}

	CXProcessEvent processEvent;
	pSection->SetSectionNumber(nLineNumber);
	pSection->AddEvent(EDataChanged);
}



