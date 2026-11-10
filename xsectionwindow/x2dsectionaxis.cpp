#include "x2dsectionaxis.h"

#include <QPainter>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QWheelEvent>

#include "xseismicsection.h"
#include "xglobal.h"
#include "xseismicdatavolume.h"
#include "xautogrid.h"
#include "x2dsectionwindow.h"
#include "xsectionscene.h"
#include "xwindowinfosection.h"
#include "xwell.h"
#include "xseismicrandomsection.h"
#include "xseismicdataline.h"
#include "x2dseismicline.h"
#include "x2dsectionview.h"
#include "xutility.h"
#include "xwindowinfosection.h"
#include "x2daxishelper.h"

CX2DSectionAxis::CX2DSectionAxis(QWidget* parent)
	:QWidget(parent)
{
	m_pWindow = dynamic_cast<CX2DSectionWindow*>(parent);
	m_pWindowInfo = m_pWindow->GetSecWindowViewInfo();
}

void CX2DSectionAxis::AddWidget(QWidget *pWidget)
{
	m_pLayout = new QGridLayout(this);
	m_pLayout->setContentsMargins(m_pWindowInfo->GetHorAxisMargin(), m_pWindowInfo->GetVerAxisMargin(), 0, 0);
	m_pLayout->addWidget(pWidget,0,0,1,1);

	m_pScene = (CXSectionScene *)(m_pWindow->GetScene());
}

void CX2DSectionAxis::paintEvent(QPaintEvent* event)
{
	if (!m_pObject || !m_pAxisX || !m_pAxisY) 
		return;

	m_pWindowInfo->SetVerAxisMargin(23* (m_listXAxisName .size()+1));

	// margin
	if (m_pLayout != NULL)
	{
		m_pLayout->setContentsMargins(m_pWindowInfo->GetHorAxisMargin(), m_pWindowInfo->GetVerAxisMargin(), 0, 0);
	}

	QPainter painter(this);

	// rect for viewport
	QRect rect = this->rect();
	rect.adjust(m_pWindowInfo->GetHorAxisMargin(), m_pWindowInfo->GetVerAxisMargin(), 0, 0);
	painter.drawRect(rect);
	
	QFont verfont(m_pWindowInfo->GetVerAnnFont(), m_pWindowInfo->GetVerAnnSize());
	QFont horfont(m_pWindowInfo->GetHorAnnFont(), m_pWindowInfo->GetHorAnnSize());
	QRectF rectScene = m_pWindow->GetSceneRect();
	m_pAxisX->SetFontandRect(horfont, rectScene, m_pWindowInfo->GetHorAxisMargin(), m_pWindowInfo->GetVerAxisMargin(), m_vecXValue);
	m_pAxisY->SetFontandRect(verfont, rectScene, m_pWindowInfo->GetHorAxisMargin(), m_pWindowInfo->GetVerAxisMargin(), m_vecYValue);

	// draw
	_Draw(&painter);

	//	Section title.
	painter.save();
	painter.setPen(QPen(QBrush(Qt::black), 4));
    painter.drawText(this->rect(), Qt::AlignHCenter | Qt::AlignTop, m_pObject->GetObjectName());
	painter.restore();

	//	For well's name.
	for (int iIdx = 0; iIdx < m_displayedWellList.size(); ++iIdx)
	{
		QPair<CXWell*, double> pair = m_displayedWellList.at(iIdx);
		painter.save();
		painter.setPen(pair.first->GetColor());
		painter.setFont(horfont);
		QFontMetrics fontmetrics(horfont);
		QRect fontRect = fontmetrics.tightBoundingRect(pair.first->GetObjectName());		
		int iPos = m_pAxisX->GetPositionFromData(pair.second);
		
		painter.drawText(iPos- fontRect.width()/2, 20, pair.first->GetObjectName());
		painter.restore();
	}
}


void CX2DSectionAxis::_SetSectionPrestack()
{
	CXSeismicSection *pSection = dynamic_cast<CXSeismicSection *>(m_pObject);	
	CXSeismicDataVolume* pDV = dynamic_cast<CXSeismicDataVolume *>(m_pScene->GetBackgroundSection(false));
	Q_ASSERT(pSection && pDV);

	// key index
	vector<int> vecKeyIndex;
	int nTraceQty;
	
	SKETraceInfo *pTraceInfo = m_pScene->GetTraceInfo(nTraceQty);
	if (!pTraceInfo)
	{
		// regular
		float fOffsetStart, fOffsetStep;
		int nOffsetNum;
		pDV->GetOffsetInfo(fOffsetStart, fOffsetStep, nOffsetNum);
		int iAxisStart, iAxisEnd;
		pSection->GetSectionRange(iAxisStart, iAxisEnd);

		CXSeismicUTMTool& utm = pDV->GetUTM();
		int iLineNumMin, iLineNumMax, iLineNumInc, iXlineNumMin, iXlineNumMax, iXlineNumInc;
		utm.GetLineNumRange(iLineNumMin, iLineNumMax, iLineNumInc, iXlineNumMin, iXlineNumMax, iXlineNumInc);
		
		m_listXAxisName << "offset";
		int iInc;
		if (pSection->GetSectionType() == eInlineSection)
		{
			iInc = iXlineNumInc;
			m_listXAxisName << "xline";
		}
		else
		{
			iInc = iLineNumInc;
			m_listXAxisName<< "inline";
		}
		int nLineQty = (iAxisEnd - iAxisStart) / iInc + 1;
		nTraceQty = nLineQty*nOffsetNum;

		m_vec2DCoord.resize(m_listXAxisName.size());
		for (int i = 0; i < m_listXAxisName.size(); ++i)
			m_vec2DCoord[i].resize(nTraceQty);

		vecKeyIndex.resize(nLineQty);
		for (int i = 0; i < nLineQty; ++i)
		{	
			vecKeyIndex[i] = i*nOffsetNum;
			for (int j = 0; j < nOffsetNum; ++j)
			{
				m_vec2DCoord[0][i*nOffsetNum + j] = fOffsetStart + j*fOffsetStep;
				m_vec2DCoord[1][i*nOffsetNum + j] = iAxisStart + i*iInc;
			}
		}
	}
	else // irregular
	{
		EXSectionType eType = pSection->GetSectionType();
		m_listXAxisName << "offset" << "azimuth";
		if (eType == eInlineSection)
		{
			m_listXAxisName << "xline";
		}
		else
		{
			m_listXAxisName << "inline";
		}
				
		m_vec2DCoord.resize(m_listXAxisName.size());
		for (int i = 0; i < m_listXAxisName.size(); ++i)
			m_vec2DCoord[i].resize(nTraceQty);

		int iInline, iXline;
		for (int i = 0; i < nTraceQty; ++i)
		{
			if (i == 0)
			{
				iInline = pTraceInfo[0].m_iLine;
				iXline = pTraceInfo[0].m_iCDP;
				vecKeyIndex.push_back(i);
			}
			else if (iInline != pTraceInfo[i].m_iLine ||
					 iXline != pTraceInfo[i].m_iCDP)
			{
				vecKeyIndex.push_back(i);
			}

			m_vec2DCoord[0][i] = pTraceInfo[i].m_iOffset;
			m_vec2DCoord[1][i] = pTraceInfo[i].m_iAzimuth;

			if (eType == eInlineSection)
			{
				m_vec2DCoord[2][i] = pTraceInfo[i].m_iCDP;
			}
			else
			{
				m_vec2DCoord[2][i] = pTraceInfo[i].m_iLine;
			}
		}
	}

	if (m_pAxisX)
		delete m_pAxisX;
	m_pAxisX = new CX2DAxisHelper(0, nTraceQty - 1, 1, false, vecKeyIndex);

	_SetXYAxis();
}

void CX2DSectionAxis::_SetRandomPrestack()
{
	auto pRandomSection = dynamic_cast<CXSeismicRandomSection*>(m_pObject);
	if (!pRandomSection)
		return;

	auto pDV = dynamic_cast<CXSeismicObject*>(m_pScene->GetBackgroundSection(false));
	Q_ASSERT(pDV);

	vector<int> vecInline, vecXline;
	pRandomSection->GetLineNumbers(vecInline, vecXline);

	// key index
	vector<int> vecKeyIndex;
	int nTraceQty;

	SKETraceInfo *pTraceInfo = m_pScene->GetTraceInfo(nTraceQty);
	if (!pTraceInfo)
	{
		// regular
		float fOffsetStart, fOffsetStep;
		int nOffsetNum;
		pDV->GetOffsetInfo(fOffsetStart, fOffsetStep, nOffsetNum);

		nTraceQty = nOffsetNum*vecInline.size();	

		m_listXAxisName << "offset" << "xline" << "inline";

		m_vec2DCoord.resize(m_listXAxisName.size());
		for (int i = 0; i < m_listXAxisName.size(); ++i)
			m_vec2DCoord[i].resize(nTraceQty);

		int nLineQty = (int)vecInline.size();
		vecKeyIndex.resize(nLineQty);

		for (int i = 0; i < nLineQty; ++i)
		{
			vecKeyIndex[i] = i*nOffsetNum;
			for (int j = 0; j < nOffsetNum; ++j)
			{
				m_vec2DCoord[0][i*nOffsetNum + j] = fOffsetStart + j*fOffsetStep;
				m_vec2DCoord[1][i*nOffsetNum + j] = vecXline[i];
				m_vec2DCoord[2][i*nOffsetNum + j] = vecInline[i];
			}
		}
	}
	else // irregular
	{
		m_listXAxisName << "offset" << "azimuth"<<"xline" << "inline";

		m_vec2DCoord.resize(m_listXAxisName.size());
		for (int i = 0; i < m_listXAxisName.size(); ++i)
			m_vec2DCoord[i].resize(nTraceQty);

		int nGatherSize = nTraceQty / vecInline.size();
		for (int i = 0; i < nTraceQty; ++i)
		{
			if (i%nGatherSize == 0)
				vecKeyIndex.push_back(i);

			m_vec2DCoord[0][i] = pTraceInfo[i].m_iOffset;
			m_vec2DCoord[1][i] = pTraceInfo[i].m_iAzimuth;
			m_vec2DCoord[2][i] = pTraceInfo[i].m_iCDP;
			m_vec2DCoord[3][i] = pTraceInfo[i].m_iLine;
		}
	}

	if (m_pAxisX)
		delete m_pAxisX;
	m_pAxisX = new CX2DAxisHelper(0, nTraceQty - 1, 1, false, vecKeyIndex);

	_SetXYAxis();

}

void CX2DSectionAxis::_SetRandomPoststack()
{
	auto pRandomSection = dynamic_cast<CXSeismicRandomSection*>(m_pObject);
	if (!pRandomSection)
		return;

	auto pDV = dynamic_cast<CXSeismicObject*>(m_pScene->GetBackgroundSection(false));
	Q_ASSERT(pDV);

	vector<int> vecInline, vecXline;
	pRandomSection->GetLineNumbers(vecInline, vecXline);

	m_listXAxisName << "xline" << "inline";

	m_vec2DCoord.resize(m_listXAxisName.size());
	for (int i = 0; i < m_listXAxisName.size(); ++i)
		m_vec2DCoord[i].resize(vecInline.size());

	std::copy(vecInline.begin(), vecInline.end(), m_vec2DCoord[1].begin());
	std::copy(vecXline.begin(), vecXline.end(), m_vec2DCoord[0].begin());

	if (m_pAxisX)
		delete m_pAxisX;
	m_pAxisX = new CX2DAxisHelper(0, pRandomSection->GetTraceNum() - 1, 1, false, pRandomSection->GetVecTPIndex());

	_SetXYAxis();
}

void CX2DSectionAxis::_SetSectionPostStack()
{
	auto pSeismicSection = dynamic_cast<CXSeismicSection*>(m_pObject);
	if (!pSeismicSection)
		return;

	double dZStart(0), dZEnd(0), dZStep(1);
	int xStart, xEnd, xStep(1);

	if (eProfile == m_eType)
	{
		int iLineNum;
		pSeismicSection->GetProfileGeometry(iLineNum, xStart, xEnd, dZStart, dZEnd);
		m_listXAxisName<<"pixel";
	}
	else
	{
		auto pDV = dynamic_cast<CXSeismicObject*>(m_pScene->GetBackgroundSection(false));
		Q_ASSERT(pDV);
		CXSeismicUTMTool& utmTool = pDV->GetUTM();
		pDV->GetSamplingRange(dZStart, dZEnd, dZStep);

		pSeismicSection->GetSectionRange(xStart, xEnd);

		if (pSeismicSection->GetSectionType() == eInlineSection)
		{
			xStep = utmTool.GetCrosslineIncrement();
			m_listXAxisName << "xline";
		}
		else if (pSeismicSection->GetSectionType() == eCrosslineSection)
		{
			xStep = utmTool.GetInlineIncrement();
			m_listXAxisName << "inline";
		}
	}

	if (m_pAxisX)
		delete m_pAxisX;
	m_pAxisX = new CX2DAxisHelper(xStart, xEnd, xStep, false);

	_SetXYAxis();

}
void CX2DSectionAxis::_Set2DLine()
{
	auto p2DLine = dynamic_cast<CX2DSeismicLine*>(m_pObject);
	if (!p2DLine)
		return;

	unsigned int *pCDP = p2DLine->GetCDPData();
	if (!pCDP)
		return;

	int nTraceQty = p2DLine->GetTraceNumber();
	if (nTraceQty < 2)
		return;

	m_listXAxisName << "CDP";
	m_vec2DCoord.resize(1);
	m_vec2DCoord[0].resize(nTraceQty);
	for (int i = 0; i < nTraceQty; ++i)
		m_vec2DCoord[0][i] = pCDP[i];


	// x
	if (m_pAxisX)
		delete m_pAxisX;
	m_pAxisX = new CX2DAxisHelper(0, nTraceQty - 1, 1, false);
	m_vecXValue.push_back(pCDP[0]);
	m_vecXValue.push_back(pCDP[nTraceQty - 1]);

	// y
	double dStart, dEnd, dStep;
	p2DLine->GetDefaultSection(true)->GetSamplingRange(dStart, dEnd, dStep);
	if (m_pAxisY)
		delete m_pAxisY;
	m_pAxisY = new CX2DAxisHelper(dStart, dEnd, dStep, true);
	m_vecYValue.push_back(dStart);
	m_vecYValue.push_back(dEnd);
}

void CX2DSectionAxis::_SetXYAxis()
{
	// X
	if (m_vec2DCoord.empty())
	{
		double dStart, dEnd, dStep;
		m_pAxisX->GetAxisRange(dStart, dEnd, dStep);
		m_vecXValue.push_back(dStart);
		m_vecXValue.push_back(dEnd);
	}
	else
	{
		int nSize = m_vec2DCoord.size();
		int nLength = m_vec2DCoord[0].size();
		if (nLength == 0)
			return;

		for (int i = 0; i < nSize; ++i)
		{
			m_vecXValue.push_back(m_vec2DCoord[i][0]);
			m_vecXValue.push_back(m_vec2DCoord[i][nLength - 1]);
			m_vecXValue.push_back(m_vec2DCoord[i][nLength / 2]);
		}
	}


	// Y
	auto pDV = dynamic_cast<CXSeismicObject*>(m_pScene->GetBackgroundSection(false));
	Q_ASSERT(pDV);

	double dZStart(0), dZEnd(0), dZStep(1);
	pDV->GetSamplingRange(dZStart, dZEnd, dZStep);

	if (m_pAxisY)
		delete m_pAxisY;
	m_pAxisY = new CX2DAxisHelper(dZStart, dZEnd, dZStep, true);
	m_vecYValue.clear();
	m_vecYValue.push_back(dZStart);
	m_vecYValue.push_back(dZEnd);
}

void CX2DSectionAxis::_DrawIndexedXAxis(QPainter* painter)
{
	double dStart, dEnd, dStep;
	m_pAxisX->GetAxisRange(dStart, dEnd, dStep);

	int nPrecision = m_pAxisX->GetPrecision();
	int nLeftMargin = m_pWindowInfo->GetHorAxisMargin();
	int nTopMargin = m_pWindowInfo->GetVerAxisMargin();
	int width, height;
	m_pWindow->GetScollbarDimension(width, height);
	QRect rect = this->rect();

	painter->save();
	painter->setPen(m_pWindowInfo->GetHorAnnColor());
	QFont font(m_pWindowInfo->GetHorAnnFont(), m_pWindowInfo->GetHorAnnSize());
	painter->setFont(font);

	QFontMetrics fontmetrics(font);
	QRect fontRect;

	int nXAxisNum = m_listXAxisName.size();
	int iPos;
	QString strValue;
	int index;
	for (double dValue = dStart; dValue <= dEnd; dValue += dStep)
	{
		iPos = m_pAxisX->GetPositionFromData(dValue);
		if (iPos > rect.right() - width + 1 || iPos < rect.left() + nLeftMargin)
			continue;

		if (m_pAxisX->IsMainTick(dValue))
		{
			painter->drawLine(iPos, nTopMargin, iPos, nTopMargin - 7);

			index = static_cast<int>((dValue - dStart) / dStep + 0.01);

			for (int i = 0; i < nXAxisNum; ++i)
			{
				// text
				strValue = QString::number(m_vec2DCoord[i][index], 'f', nPrecision);
				fontRect = fontmetrics.tightBoundingRect(strValue);

				painter->drawText(iPos - fontRect.width() / 2,
					nTopMargin - fontRect.height()*(i + 1) - 11 * i, strValue);

			}
		}
		else if (m_pAxisX->IsMinorTick(dValue))
		{
			painter->drawLine(iPos, nTopMargin, iPos, nTopMargin - 5);
		}
	}

	// X axis lables
	for (int i = 0; i < nXAxisNum; ++i)
	{
		// text
		strValue = m_listXAxisName.at(i);
		fontRect = fontmetrics.tightBoundingRect(strValue);

		painter->drawText(nLeftMargin - 22 - fontRect.width(), nTopMargin - fontRect.height()*(i + 1) - 11 * i, strValue);
	}


	painter->restore();
}

void CX2DSectionAxis::_DrawContinuousXAxis(QPainter* painter)
{
	double dStart, dEnd, dStep;
	m_pAxisX->GetAxisRange(dStart, dEnd, dStep);

	int nPrecision = m_pAxisX->GetPrecision();
	int nLeftMargin = m_pWindowInfo->GetHorAxisMargin();
	int nTopMargin = m_pWindowInfo->GetVerAxisMargin();
	int width, height;
	m_pWindow->GetScollbarDimension(width, height);
	QRect rect = this->rect();

	painter->save();
	painter->setPen(m_pWindowInfo->GetHorAnnColor());
	QFont font(m_pWindowInfo->GetHorAnnFont(), m_pWindowInfo->GetHorAnnSize());
	painter->setFont(font);

	QFontMetrics fontmetrics(font);
	QRect fontRect;

	double iPos;
	QString strValue;
	for (double dValue = dStart; dValue <= dEnd; dValue += dStep)
	{
		iPos = m_pAxisX->GetPositionFromData(dValue);
		if (iPos > rect.right() - width || iPos < rect.left() + nLeftMargin)
			continue;

		if (m_pAxisX->IsMainTick(dValue))
		{
			painter->drawLine(iPos, nTopMargin, iPos, nTopMargin - 7);

			// text
			strValue = QString::number(dValue, 'f', nPrecision);
			fontRect = fontmetrics.tightBoundingRect(strValue);

			painter->drawText(iPos - fontRect.width() / 2, nTopMargin - fontRect.height(), strValue);
		}
		else if (m_pAxisX->IsMinorTick(dValue))
		{
			painter->drawLine(iPos, nTopMargin, iPos, nTopMargin - 5);
		}
	}

	// X axis lables
	strValue = m_listXAxisName.front();
	fontRect = fontmetrics.tightBoundingRect(strValue);
	painter->drawText(nLeftMargin - 22 - fontRect.width(), nTopMargin - fontRect.height(), strValue);
	
	// restore
	painter->restore();
}

void CX2DSectionAxis::_DrawY(QPainter* painter)
{
	double dStart, dEnd, dStep;
	m_pAxisY->GetAxisRange(dStart, dEnd, dStep);

	int nPrecision = m_pAxisX->GetPrecision();
	int nLeftMargin = m_pWindowInfo->GetHorAxisMargin();
	int nTopMargin = m_pWindowInfo->GetVerAxisMargin();
	int width, height;
	m_pWindow->GetScollbarDimension(width, height);
	QRect rect = this->rect();

	QFont font(m_pWindowInfo->GetVerAnnFont(), m_pWindowInfo->GetVerAnnSize());

	painter->save();
	painter->setPen(m_pWindowInfo->GetVerAnnColor());
	painter->setFont(font);

	QFontMetrics fontmetrics(font);
	QRect fontRect;

	double iPos;
	QString strValue;

	if (dStep >0.1) // ms
	{
		dStep = 1.;
	}
	else
	{
		dStep = 0.001; //s
	}

	for (double dValue = dStart; dValue <= dEnd; dValue += dStep)
	{
		iPos = m_pAxisY->GetPositionFromData(dValue);

		if (iPos > rect.bottom() - height || iPos < rect.top() + nTopMargin)
			continue;

		if (m_pAxisY->IsMainTick(dValue))
		{
			// main tick
			painter->drawLine(nLeftMargin, iPos, nLeftMargin - 7, iPos);

			// text
			strValue = QString::number(dValue, 'f', nPrecision);
			fontRect = fontmetrics.tightBoundingRect(strValue);

			painter->drawText(nLeftMargin - 22 - fontRect.width(), iPos + fontRect.height() / 2, strValue);
		}
		else if (m_pAxisY->IsMinorTick(dValue))
		{
			painter->drawLine(nLeftMargin, iPos, nLeftMargin - 5, iPos);
		}
	}

	painter->restore();

	// Y axis lable
	painter->save();
	painter->setPen(m_pWindowInfo->GetVerAnnColor());
	painter->setFont(font);

	QString strYName = "Time";
	int heightYAxis = fontmetrics.tightBoundingRect(strYName).height();

	double dHeight = m_pWindow->GetView()->viewport()->rect().height() / 2 + nTopMargin;
	painter->translate(heightYAxis / 2, dHeight);
	painter->rotate(-90);
	painter->drawText(0, heightYAxis * 3 / 2, strYName);

	painter->restore();	
}

void CX2DSectionAxis::AddWellName(QPair<CXWell* ,double> wellName)
{
	bool bExist(false);
	for(int iIdx = 0; iIdx < m_displayedWellList.size();++iIdx)
	{
		QPair<CXWell* ,double> pair = m_displayedWellList.at(iIdx);
		QUuid uid = pair.first->GetObjectID();
		if (wellName.first->GetObjectID() == uid)
		{
			m_displayedWellList[iIdx].second = wellName.second;
			bExist = true;
			break;
		}
	}
	if (!bExist)
	{
		m_displayedWellList.append(wellName);
	}
	repaint();
}
void CX2DSectionAxis:: RemoveWellName(CXWell *pWell)
{
	for(int iIdx = 0; iIdx < m_displayedWellList.size();++iIdx)
	{
		QPair<CXWell * ,double> pair = m_displayedWellList.at(iIdx);
		QUuid uid = pair.first->GetObjectID();
		if (pWell->GetObjectID() == uid)
		{
			m_displayedWellList.removeAt(iIdx);
			break;
		}
	}
	repaint();
}
void CX2DSectionAxis::SetDisplaySection(CXObject *pObj)
{
	m_pObject = pObj;
	if (!m_pObject)
	{
		repaint();
		return;
	}	

	// set data type
	_SetDataTypeandResetDrawData();


	switch (m_eType)
	{
	case eProfile:
	case eSectionPoststack:
		_SetSectionPostStack();
		break;

	case eSectionPrestack:
		_SetSectionPrestack();
		break;

	case eRandomPrestack:
		_SetRandomPrestack();
		break;

	case eRandomPostack:
		_SetRandomPoststack();
		break;

	case e2DLine:
		_Set2DLine();
		break;

	default:
		break;
	}

	repaint();
}	

void CX2DSectionAxis::_SetDataTypeandResetDrawData()
{
	auto pSection = dynamic_cast<CXSeismicSection*>(m_pObject);
	auto pRandomSection = dynamic_cast<CXSeismicRandomSection*>(m_pObject);
	auto p2DLine = dynamic_cast<CX2DSeismicLine*>(m_pObject);

	auto pDV = dynamic_cast<CXSeismicDataVolume*>(m_pScene->GetBackgroundSection(false));
	if (!pDV)
		return;

	if (pSection)
	{
		if (eInlineProfile == pSection->GetSectionType())
			m_eType = eProfile;
		else
		{
			if (pDV->IsPrestack())
				m_eType = eSectionPrestack;
			else
				m_eType = eSectionPoststack;
		}
	}
	else if (pRandomSection)
	{
		if (pDV->IsPrestack())
			m_eType = eRandomPrestack;
		else
			m_eType = eRandomPostack;
	}
	else if (p2DLine)
	{
		m_eType = e2DLine;
	}
	else
	{
		Q_ASSERT(false);
	}

	// clear data
	m_vecXValue.clear();
	m_vecYValue.clear();
	m_vec2DCoord.clear();
	m_listXAxisName.clear();

	if (m_pAxisX)
	{
		delete m_pAxisX;
		m_pAxisX = nullptr;
	}
	if (m_pAxisY)
	{
		delete m_pAxisY;
		m_pAxisY = nullptr;
	}
}

void CX2DSectionAxis::_Draw(QPainter* painter)
{
	// x axis
	if (m_eType == eProfile || m_eType == eSectionPoststack)
	{
		_DrawContinuousXAxis(painter);
	}
	else if (m_eType == eSectionPrestack || 
			 m_eType == eRandomPrestack ||
		     m_eType == eRandomPostack ||
		     m_eType == e2DLine)
	{
		_DrawIndexedXAxis(painter);
	}

	// y axis
	_DrawY(painter);
}
