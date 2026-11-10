#include "xviewutility.h"
#include <QDesktopWidget>
#include <QApplication>
#include "xsectionscene.h"
#include "xwindowinfosection.h"
#include "xseismicobject.h"

void NXViewUtility::GetMMPerDPI(float& fMMX, float& fMMY)
{
	QWidget* pDesktop = QApplication::desktop();

	float fLogicX = pDesktop->physicalDpiX();
	float fLogicY = pDesktop->physicalDpiY();

	float fCmPerInch = 2.54f;

	fMMX = fCmPerInch / fLogicX*10.f;
	fMMY = fCmPerInch / fLogicY*10.f;
}

void NXViewUtility::GetSizeFromViewInfo(CXWindowInfoSection* pViewInfo, CXSectionScene* pScene, double& dWidth, double& dHeight)
{
	// Section size
	int nJ, nK;
	pScene->GetSectionDimension(nJ, nK);
	auto pDV = dynamic_cast<CXSeismicObject*>(pScene->GetBackgroundSection(false));
	if (!pDV)
		return;

	double dSamplingRate = pDV->GetSampleInterval();	

	// Set size
	float fMMX, fMMY;
	GetMMPerDPI(fMMX, fMMY);

	// traces per mm
	double fHScale = pViewInfo->GetTraceScale() / 10.;

	// ms per mm
	double fVScale = pViewInfo->GetVerScale() / 10.;

	dWidth = nJ / fHScale / fMMX;
	dHeight = nK / (fVScale / dSamplingRate) / fMMY;
}

void NXViewUtility::SetViewInfoFromSize(CXWindowInfoSection* pViewInfo, CXSectionScene* pScene, int nWidth, int nHeight)
{
	// Section size
	int nJ, nK;
	pScene->GetSectionDimension(nJ, nK);

	auto pDV = dynamic_cast<CXSeismicObject*>(pScene->GetBackgroundSection(false));
	if (!pDV)
		return;

	double dSamplingRate = pDV->GetSampleInterval();


	// Set size
	float fMMX, fMMY;
	GetMMPerDPI(fMMX, fMMY);

	double fHScale = nJ / (nWidth*fMMX);
	double fVScale = (nK / (nHeight*fMMY))*dSamplingRate;

	pViewInfo->SetTraceScale(10.f*fHScale);
	pViewInfo->SetVerScale(10.f*fVScale);
}

