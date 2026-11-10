#include "xbmsurveybuilder.h"

#include <osg/Geometry>
#include <osg/LineWidth>
#include <osgText/Text>
#include <QDebug>

#include "x3dutility.h"
#include "x3dsurvey.h"
#include "xseismicutmtool.h"
#include "xglobal.h"
#include "x3dglobalcoordmap.h"
#include "xviewinfo3dsurvey.h"
#include "x3dbuilderfactory.h"
#include "xautogrid.h"

BEGIN_REGISTER_BUILDER_TO_FACTORY(CXBMSurveyBuilder)
{ EX3DSurvey, e3DBaseMap }
END_REGISTER_BUILDER_TO_FACTORY(CXBMSurveyBuilder)

CXBMSurveyBuilder::CXBMSurveyBuilder()
: CX3DBuilderAbstract()
{

}

CXBMSurveyBuilder::~CXBMSurveyBuilder()
{

}

osg::ref_ptr<osg::Group> CXBMSurveyBuilder::Build(QUuid objId)
{
	m_pSurvey = dynamic_cast<CX3DSurvey*>(::GetObjectByID(objId));
	m_pViewInfo = dynamic_cast<CXViewInfo3DSurvey*>(m_pCurWin->GetObjectViewInfo(objId));
	if (!m_pSurvey || !m_pViewInfo)
		return nullptr;

	const CXSeismicUTMTool& utmTool = m_pSurvey->GetUTM();
	m_firstInline = utmTool.GetFirstInline();
	m_lastInline = utmTool.GetLastInline();
	m_firstXline = utmTool.GetFirstCrossline();
	m_lastXline = utmTool.GetLastCrossline();

	m_pSurveyNode = new osg::Geode;
	m_pSurveyNode->setUserValue("objID", m_pSurvey->GetObjectID().toString().toStdString());
	m_pSurveyNode->addDrawable(_BuildBoundaryBox());
	m_pSurveyNode->addDrawable(_BuildSeismicLine());
	m_pSurveyNode->addDrawable(_BuildTracePoints());
	m_pSurveyNode->addDrawable(_BuildSurveyLabel());

	m_pBuilderNode = new osg::Group;
	m_pBuilderNode->addChild(m_pSurveyNode.get());
	m_pBuilderNode->addChild(_BuildOrUpdateTickMarks());

	return m_pBuilderNode;
}

void CXBMSurveyBuilder::UpdateNode(EEventType eType)
{
	if (eType == EInfoChanged)
	{
		_UpdateBoundaryBox();

		m_pSurveyNode->removeDrawable(m_pSeismicLineGeom);
		m_pSurveyNode->addDrawable(_BuildSeismicLine());

		m_pSurveyNode->removeDrawable(m_pTracePointsGeom);
		m_pSurveyNode->addDrawable(_BuildTracePoints());

		m_pSurveyNode->removeDrawable(m_pSurveyLabel);
		m_pSurveyNode->addDrawable(_BuildSurveyLabel());

		m_pBuilderNode->removeChild(m_pTickMarksNode);
		m_pBuilderNode->addChild(_BuildOrUpdateTickMarks());
	}
}

osg::Vec3 CXBMSurveyBuilder::_LT2Local(int iInline, int iXline) const
{
	double dX, dY;
	const CXSeismicUTMTool& utmTool = m_pSurvey->GetUTM();
	utmTool.LineToXY(iInline, iXline, dX, dY);
	osg::Vec3 vecLocal;
	m_pCoordMap->MapWorldToLocal(osg::Vec3d(dX, dY, 0.0), vecLocal);
	vecLocal.z() = -1.f;

	return vecLocal;
}

float CXBMSurveyBuilder::_GetMarkLength(int iMax, const std::string& strFont, int iFontSize, bool isInline)
{
	QString markMax = QString(isInline ? "IL%1" : "XL%1").arg(iMax);

	osg::ref_ptr<osgText::Text> pMark = new osgText::Text;
	pMark->setFont(strFont);
	pMark->setCharacterSize(iFontSize * 100);
	pMark->setAxisAlignment(osgText::Text::SCREEN);
	pMark->setCharacterSizeMode(osgText::TextBase::OBJECT_COORDS_WITH_MAXIMUM_SCREEN_SIZE_CAPPED_BY_FONT_HEIGHT);
	pMark->setText(markMax.toStdString());

	const osg::BoundingBox& markBox = pMark->getBoundingBox();
	return markBox.xMax() - markBox.xMin();
}

std::pair<double, double> CXBMSurveyBuilder::_CalcTicksGrid(int& iFirstInline, int& iLastInline, int& iInlineStep, int& iFirstXline, int& iLastXline, int& iXlineStep)
{
	const std::string& fontName = m_pViewInfo->GetTickmarksFont().toStdString();
	int fontSize = m_pViewInfo->GetTickmarksFontSize();

	osg::Vec3 vecFIFX = _LT2Local(m_firstInline, m_firstXline);
	osg::Vec3 vecFILX = _LT2Local(m_firstInline, m_lastXline);
	osg::Vec3 vecLILX = _LT2Local(m_lastInline, m_lastXline);

	double dInlineLen = (vecFILX - vecFIFX).length();
	double dXlineLen = (vecLILX - vecFILX).length();

	float fInlineMarkLen = _GetMarkLength(m_lastInline, fontName, fontSize);
	float fXlineMarkLen = _GetMarkLength(m_lastXline, fontName, fontSize, false);

	int nInlineMark = qMax(qRound(dXlineLen / (fInlineMarkLen * 1.2)), 1);
	int nXlineMark = qMax(qRound(dInlineLen / (fXlineMarkLen * 1.2)), 1);

	CXAutoGrid::AutoGrid(m_firstInline, m_lastInline, nInlineMark, iFirstInline, iLastInline, iInlineStep);
	CXAutoGrid::AutoGrid(m_firstXline, m_lastXline, nXlineMark, iFirstXline, iLastXline, iXlineStep);

	return std::make_pair(dInlineLen, dXlineLen);
}

void CXBMSurveyBuilder::_CalcTickVerticesAndBuildMarks(int iLineNo, float fTickSize, bool bInline)
{
	// vertex
	osg::Vec3 firstLocalPoint = bInline ? _LT2Local(iLineNo, m_firstXline) : _LT2Local(m_firstInline, iLineNo);
	osg::Vec3 lastLocalPoint = bInline ? _LT2Local(iLineNo, m_lastXline) : _LT2Local(m_lastInline, iLineNo);

	osg::Vec3 vecNormal = lastLocalPoint - firstLocalPoint;
	vecNormal.normalize();

	if ((bInline && m_pViewInfo->GetInlineAnnotationOnBegin()) || (!bInline && m_pViewInfo->GetXlineAnnotationOnBegin()))
	{
		m_pTickVertex->push_back(firstLocalPoint - vecNormal * fTickSize);
		m_pTickVertex->push_back(firstLocalPoint);
	}

	if ((bInline && m_pViewInfo->GetInlineAnnotationOnEnd()) || (!bInline && m_pViewInfo->GetXlineAnnotationOnEnd()))
	{
		m_pTickVertex->push_back(lastLocalPoint);
		m_pTickVertex->push_back(lastLocalPoint + vecNormal * fTickSize);
	}

	// Marks
	QString strMark = QString(bInline ? "IL%1" : "XL%1").arg(iLineNo);
	const QColor& color = m_pViewInfo->GetTickmarksColor();

	osgText::Text* pFirstMark = new osgText::Text;
	pFirstMark->setFont(::GetOSGFontPath(m_pViewInfo->GetTickmarksFont()));
	pFirstMark->setCharacterSize(m_pViewInfo->GetTickmarksFontSize() * 100);
	pFirstMark->setAxisAlignment(osgText::Text::SCREEN);
	pFirstMark->setAlignment(osgText::Text::CENTER_CENTER);
	pFirstMark->setCharacterSizeMode(osgText::TextBase::OBJECT_COORDS_WITH_MAXIMUM_SCREEN_SIZE_CAPPED_BY_FONT_HEIGHT);
	pFirstMark->setText(strMark.toStdString());
	pFirstMark->setColor(osg::Vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF()));

	const osg::BoundingBox& markBox = pFirstMark->getBoundingBox();
	float cosWithX = vecNormal * osg::Vec3(1.f, 0.f, 0.f);
	bool bHorizon = 0 <= cosWithX && cosWithX <= std::cos(M_PI_4);
	float fMarkOffset = fTickSize + (bHorizon ? (markBox.xMax() - markBox.xMin()) / 2 : (markBox.yMax() - markBox.yMin()) / 2);
	pFirstMark->setPosition(firstLocalPoint - vecNormal * fMarkOffset);

	if ((bInline && m_pViewInfo->GetInlineAnnotationOnBegin()) || (!bInline && m_pViewInfo->GetXlineAnnotationOnBegin()))
	{
		m_pTickMarksNode->addDrawable(pFirstMark);
	}

	osgText::Text* pLastMark = new osgText::Text(*pFirstMark, osg::CopyOp::DEEP_COPY_ALL);
	pLastMark->setPosition(lastLocalPoint + vecNormal * fMarkOffset);

	if ((bInline && m_pViewInfo->GetInlineAnnotationOnEnd()) || (!bInline && m_pViewInfo->GetXlineAnnotationOnEnd()))
	{
		m_pTickMarksNode->addDrawable(pLastMark);
	}
}

osg::Vec3Array* CXBMSurveyBuilder::_BuildTickVertexAndMarks()
{
	int iUniFirstInline = 0, iUniLastInline = -1, iInlineStep = 1, iUniFirstXline = 0, iUniLastXline = -1, iXlineStep = 1;
	std::pair<double, double> lineBox = _CalcTicksGrid(iUniFirstInline, iUniLastInline, iInlineStep, iUniFirstXline, iUniLastXline, iXlineStep);

	m_pTickVertex = new osg::Vec3Array;
	m_pTickMarksNode->removeDrawables(1, m_pTickMarksNode->getNumDrawables() - 1);

	for (int i = iUniFirstInline; i <= iUniLastInline; i += iInlineStep)
	{
		_CalcTickVerticesAndBuildMarks(i, lineBox.first * 0.01, true);
	}

	for (int i = iUniFirstXline; i <= iUniLastXline; i += iXlineStep)
	{
		_CalcTickVerticesAndBuildMarks(i, lineBox.second * 0.01, false);
	}

	return m_pTickVertex.get();
}

osg::Geometry* CXBMSurveyBuilder::_BuildBoundaryBox()
{
	m_pBoundaryGeom = new osg::Geometry;

	osg::Vec3Array* pVertex = new osg::Vec3Array(4);
	(*pVertex)[0] = _LT2Local(m_firstInline, m_firstXline);
	(*pVertex)[1] = _LT2Local(m_firstInline, m_lastXline);
	(*pVertex)[2] = _LT2Local(m_lastInline, m_lastXline);
	(*pVertex)[3] = _LT2Local(m_lastInline, m_firstXline);
	m_pBoundaryGeom->setVertexArray(pVertex);
	m_pBoundaryGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP, 0, pVertex->size()));

	_UpdateBoundaryBox();

	return m_pBoundaryGeom.get();
}

osg::Geometry* CXBMSurveyBuilder::_BuildSeismicLine()
{
	if (!m_pViewInfo || !m_pViewInfo->GetSeismicLineVisible())
		return nullptr;

	m_pSeismicLineGeom = new osg::Geometry;

	int iUniFirstInline, iUniLastInline, iInlineStep, iUniFirstXline, iUniLastXline, iXlineStep;
	_CalcTicksGrid(iUniFirstInline, iUniLastInline, iInlineStep, iUniFirstXline, iUniLastXline, iXlineStep);

	osg::Vec3Array* pVertex = new osg::Vec3Array;
	for (int i = iUniFirstInline; i <= iUniLastInline; i += iInlineStep)
	{
		pVertex->push_back(_LT2Local(i, m_firstXline));
		pVertex->push_back(_LT2Local(i, m_lastXline));
	}

	for (int i = iUniFirstXline; i <= iUniLastXline; i += iXlineStep)
	{
		pVertex->push_back(_LT2Local(m_firstInline, i));
		pVertex->push_back(_LT2Local(m_lastInline, i));
	}
	m_pSeismicLineGeom->setVertexArray(pVertex);
	m_pSeismicLineGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, pVertex->size()));

	const QColor& color = m_pViewInfo->GetSeismicLineColor();
	osg::Vec4Array* pColors = new osg::Vec4Array(1);
	(*pColors)[0].set(color.redF(), color.greenF(), color.blueF(), color.alphaF());
	m_pSeismicLineGeom->setColorArray(pColors, osg::Array::BIND_OVERALL);

	osg::StateSet* pStateSet = m_pSeismicLineGeom->getOrCreateStateSet();
	pStateSet->setAttributeAndModes(new osg::LineWidth(m_pViewInfo->GetSeismicLineWidth()), osg::StateAttribute::ON);

	return m_pSeismicLineGeom.get();
}

osg::Geometry* CXBMSurveyBuilder::_BuildTracePoints()
{
	if (!m_pViewInfo || !m_pViewInfo->GetTracePointVisible())
		return nullptr;

	m_pTracePointsGeom = new osg::Geometry;

	int iUniFirstInline, iUniLastInline, iInlineStep, iUniFirstXline, iUniLastXline, iXlineStep;
	std::pair<double, double> lineBox = _CalcTicksGrid(iUniFirstInline, iUniLastInline, iInlineStep, iUniFirstXline, iUniLastXline, iXlineStep);
	double symbolSize = qMax(lineBox.first, lineBox.second) * 0.01;

	osg::Vec3Array* pVertex = new osg::Vec3Array;

	switch (m_pViewInfo->GetTracePointSymbol())
	{
	case 0:
	{
		for (int i = iUniFirstInline; i <= iUniLastInline; i += iInlineStep)
		{
			for (int j = iUniFirstXline; j <= iUniLastXline; j += iXlineStep)
			{
				pVertex->push_back(_LT2Local(i, j));
			}
		}

		m_pTracePointsGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, pVertex->size()));
		break;
	}
	case 1:
	{
		for (int i = iUniFirstInline; i <= iUniLastInline; i += iInlineStep)
		{
			for (int j = iUniFirstXline; j <= iUniLastXline; j += iXlineStep)
			{
				osg::Vec3 center = _LT2Local(i, j);
				pVertex->push_back(center - osg::Vec3(symbolSize, 0.f, 0.f));
				pVertex->push_back(center + osg::Vec3(symbolSize, 0.f, 0.f));
				pVertex->push_back(center - osg::Vec3(0.f, symbolSize, 0.f));
				pVertex->push_back(center + osg::Vec3(0.f, symbolSize, 0.f));
			}
		}

		m_pTracePointsGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, pVertex->size()));
		break;
	}
	case 2:
	{
		for (int i = iUniFirstInline; i <= iUniLastInline; i += iInlineStep)
		{
			for (int j = iUniFirstXline; j <= iUniLastXline; j += iXlineStep)
			{
				osg::Vec3 center = _LT2Local(i, j);
				pVertex->push_back(center + osg::Vec3(-symbolSize, -symbolSize, 0.f));
				pVertex->push_back(center + osg::Vec3(symbolSize, symbolSize, 0.f));
				pVertex->push_back(center + osg::Vec3(-symbolSize, symbolSize, 0.f));
				pVertex->push_back(center + osg::Vec3(symbolSize, -symbolSize, 0.f));
			}
		}

		m_pTracePointsGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, pVertex->size()));
		break;
	}
	default:
		throw std::invalid_argument("no this symbol.");
	}

	m_pTracePointsGeom->setVertexArray(pVertex);

	const QColor& color = m_pViewInfo->GetTracePointColor();
	osg::Vec4Array* pColors = new osg::Vec4Array(1);
	(*pColors)[0].set(color.redF(), color.greenF(), color.blueF(), color.alphaF());
	m_pTracePointsGeom->setColorArray(pColors, osg::Array::BIND_OVERALL);

	return m_pTracePointsGeom.get();
}

osgText::Text* CXBMSurveyBuilder::_BuildSurveyLabel()
{
	if (!m_pViewInfo->GetSurveyNameVisible())
		return nullptr;

	const QColor& color = m_pViewInfo->GetSurveyNameColor();

	m_pSurveyLabel = new osgText::Text;

	m_pSurveyLabel->setFont(::GetOSGFontPath(m_pViewInfo->GetSurveyNameFont()));
	m_pSurveyLabel->setCharacterSize(m_pViewInfo->GetSurveyNameFontSize() * 100);
	m_pSurveyLabel->setAxisAlignment(osgText::Text::SCREEN);
	m_pSurveyLabel->setAlignment(osgText::Text::RIGHT_CENTER);
	m_pSurveyLabel->setCharacterSizeMode(osgText::TextBase::OBJECT_COORDS_WITH_MAXIMUM_SCREEN_SIZE_CAPPED_BY_FONT_HEIGHT);
	m_pSurveyLabel->setText(m_pSurvey->GetObjectName().toStdString());
	m_pSurveyLabel->setColor(osg::Vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF()));
	m_pSurveyLabel->setPosition(_LT2Local(m_firstInline, m_firstXline));

	return m_pSurveyLabel.get();
}

osg::Geode* CXBMSurveyBuilder::_BuildOrUpdateTickMarks()
{
	if (!m_pViewInfo || !m_pViewInfo->GetTickmarksVisible())
		return nullptr;

	m_pTickMarksNode = new osg::Geode;

	if (m_pTickMarksNode->getNumDrawables() == 0)
	{
		m_pTickMarksNode->addDrawable(new osg::Geometry);
	}

	osg::Geometry* pTickGeom = dynamic_cast<osg::Geometry*>(m_pTickMarksNode->getDrawable(0));

	pTickGeom->setVertexArray(_BuildTickVertexAndMarks());
	if (pTickGeom->getNumPrimitiveSets() == 0)
	{
		pTickGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, m_pTickVertex->size()));
	}
	else
	{
		pTickGeom->setPrimitiveSet(0, new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, m_pTickVertex->size()));
	}

	const QColor& tickColor = m_pViewInfo->GetBoundaryLineColor();
	osg::Vec4Array* pColors = new osg::Vec4Array(1);
	(*pColors)[0].set(tickColor.redF(), tickColor.greenF(), tickColor.blueF(), tickColor.alphaF());
	pTickGeom->setColorArray(pColors, osg::Array::BIND_OVERALL);

	osg::StateSet* pStateSet = pTickGeom->getOrCreateStateSet();
	pStateSet->setAttributeAndModes(new osg::LineWidth(m_pViewInfo->GetBoundaryLineWidth()), osg::StateAttribute::ON);

	return m_pTickMarksNode.get();
}

void CXBMSurveyBuilder::_UpdateBoundaryBox()
{
	if (!m_pViewInfo || !m_pBoundaryGeom.valid())
		return;

	const QColor& color = m_pViewInfo->GetBoundaryLineColor();
	osg::Vec4Array* pColors = new osg::Vec4Array(1);
	(*pColors)[0].set(color.redF(), color.greenF(), color.blueF(), color.alphaF());
	m_pBoundaryGeom->setColorArray(pColors, osg::Array::BIND_OVERALL);

	osg::StateSet* pStateSet = m_pBoundaryGeom->getOrCreateStateSet();
	pStateSet->setAttributeAndModes(new osg::LineWidth(m_pViewInfo->GetBoundaryLineWidth()), osg::StateAttribute::ON);
}