#include "xfile3dsurface.h"

#include <cassert>
#include <qmessagebox.h>

#include "ximport3dsurfacemanager.h"
#include "xproject.h"
#include "xglobal.h"
#include "xtree.h"
#include "xgeneralfolder.h"
#include "xseismicutmtool.h"
#include "xfunctiontemplate.h"
#include "x3dhorizon.h"
#include "x3dsurvey.h"

CXFile3DSurface::CXFile3DSurface(EImportFileType eFileType, const QString& strFileName)
	:CXASCIIFile(eFileType, strFileName)
{
	m_eDomainType = eDepthDomain;
	m_bNegateZ = false;

	m_pSelectedUTM = nullptr;
	m_pGeometrySurface = nullptr;


	m_sListAttributes.append("X");
	m_sListAttributes.append("Y");
	m_sListAttributes.append("Z");

	m_pImportMgr = new CXImport3DSurfaceManager(strFileName, eFileType);
}

CXFile3DSurface::~CXFile3DSurface()
{
	if (m_pImportMgr)
	{
		delete m_pImportMgr;
		m_pImportMgr = nullptr;
	}
}

bool CXFile3DSurface::CheckSelectedColumns(QStringList& sListChosenColumn)
{
	if (!sListChosenColumn.contains("Z"))
	{
		QMessageBox::warning(0, g_strProductName, "Z column must be selected!");
		return false;
	}

	bool bXY = false, bLine = false;
	if (sListChosenColumn.contains("X") && sListChosenColumn.contains("Y"))
		bXY = true;
	if (sListChosenColumn.contains("Inline") && sListChosenColumn.contains("Xline"))
		bLine = true;

	if (!bXY && !bLine)
	{
		QMessageBox::warning(0, g_strProductName, "X, Y columns or Inline, Xline columns must be selected!");
		return false;
	}

	return true;
}

bool CXFile3DSurface::ParseData()
{
	if (!m_pImportMgr->VerifyFileFormat(*GetDelimiter(), GetChosenColumns(), GetImportFrom(), GetImportTo(), GetInvalid()))
		return false;

	return m_pImportMgr->ImportData();
}

bool CXFile3DSurface::SetAdditionalFile(const QString& strFileName)
{
	CXImport3DSurfaceManager* pTmpMng = new CXImport3DSurfaceManager(strFileName, GetFileType());
	if (m_pImportMgr)
	{
		pTmpMng->CopyPara(m_pImportMgr);
		delete m_pImportMgr;
	}
	m_pImportMgr = pTmpMng;

	return ParseData();
}

bool CXFile3DSurface::Import()
{
	// conversion ratios
	QList<float> listRatios = GetAttributeUnitRatio();
	float fZFactor = GetNegateZ() == true ? -1.f : 1.0f;
	auto lastIndex = listRatios.size() - 1;
	m_pImportMgr->SetUnitConversionRatios(listRatios.at(lastIndex - 2), listRatios.at(lastIndex - 1), listRatios.at(lastIndex)*fZFactor);

	// Create 3-D surfaces
	if (!_CreateObj())
		return false;

	if (m_pGeometrySurface)
	{
		// add data
		for (int i = 0; i < m_listOutput.size(); ++i)
		{
			m_listOutput.at(i)->SetObjectType(EX3DHorizonAtt);
			QString strObjName = m_pGeometrySurface->GetUnallocatedName(m_listOutput.at(i)->GetObjectName());
			m_listOutput.at(i)->SetObjectName(strObjName);
			m_pGeometrySurface->AddChild(m_listOutput.at(i));

			// Add node
			::AddObjectEvent(m_listOutput.at(i));
		}
	}
	else
	{
		// Add data to the project 
		CXGeneralFolder* pSurfaceFolder = NULL;
		if (m_listOutput.at(0)->GetObjectType() == EX3DSurface)
			pSurfaceFolder = dynamic_cast<CXGeneralFolder*>(::GetRootObjectFolder(EXSurfaceFolder));
		else if (m_listOutput.at(0)->GetObjectType() == EX3DHorizon)
		{
			CX3DHorizon *pHorizon = (CX3DHorizon *)m_listOutput.at(0);
			CX3DSurvey *pSurvey = (CX3DSurvey *)(::GetObjectByID(pHorizon->GetSurveyID()));
			pSurfaceFolder = dynamic_cast<CXGeneralFolder*>(pSurvey->GetFolder(EXHorizonFolder));
		}
		assert(pSurfaceFolder);

		for (int i = 0; i < m_listOutput.size(); ++i)
		{
			QString strObjName = pSurfaceFolder->GetUnallocatedName(m_listOutput.at(i)->GetObjectName());
			m_listOutput.at(i)->SetObjectName(strObjName);
			pSurfaceFolder->AddChild(m_listOutput.at(i));

			// Add node
			::AddObjectEvent(m_listOutput.at(i));
		}
	}

	return true;
}


bool CXFile3DSurface::_CreateObj()
{
	bool bInline, bXline, bX, bY, bI, bJ;
	m_pImportMgr->GetDataFlag(bInline, bXline, bX, bY, bI, bJ);

	if(m_bWithoutZone)
		m_pImportMgr->WipeStripNumber();

	if (m_pSelectedUTM != NULL)	   // have UTM
	{
		if (m_pSelectedUTM->GetNI() == 0)
		{
			//	It's an empty utm, create new one!
			CXSeismicUTMTool seismicUTM;
			m_pImportMgr->GuessUTMTool(&seismicUTM, m_bWithoutZone);

			//	Create the new Survey!
			CX3DSurvey *pSurvey = new CX3DSurvey(seismicUTM, "Survey");
			::GetProject()->AddChild(pSurvey);

			::AddObjectEvent(pSurvey);

			m_listOutput.clear();
			int nHorizonCount = m_pImportMgr->GetHorizonNum();
			QStringList strListHorizonName = m_pImportMgr->GetHorizonListName();

			for (int i = 0; i < nHorizonCount; ++i)
			{
				QString strName = strListHorizonName[i];
				CX3DSurface* pSurface = NULL;

				pSurface = new CX3DHorizon(pSurvey->GetObjectID(), seismicUTM, strName);

				m_pImportMgr->ConvertColumnDataToSurface(pSurface, &seismicUTM, i, CXImport3DSurfaceManager::e_H_Line_XY);

				m_listOutput.append(pSurface);
			}

			return true;
		}

		if (bInline && bXline)   // have inline and xline
		{
			int iInlineStart, iInlineEnd, iInlineInc, iXlineStart, iXlineEnd, iXlineInc;
			int iInlineFirstSelect, iInlineEndSelect, iInlineIncSelect, iXlineFirstSelect, iXlineEndSelect, iXlineIncSelect;
			m_pImportMgr->GetLineRange(iInlineStart, iInlineEnd, iInlineInc, iXlineStart, iXlineEnd, iXlineInc);
			m_pSelectedUTM->GetLineNumRange(iInlineFirstSelect, iInlineEndSelect, iInlineIncSelect, iXlineFirstSelect, iXlineEndSelect, iXlineIncSelect);

			//bool b1 = IsBound(iInlineStart, qMin(iInlineFirstSelect, iInlineEndSelect), qMax(iInlineFirstSelect, iInlineEndSelect));
			//bool b2 = IsBound(iInlineEnd,   qMin(iInlineFirstSelect, iInlineEndSelect), qMax(iInlineFirstSelect, iInlineEndSelect));
			//bool b3 = IsBound(iXlineStart,  qMin(iXlineFirstSelect, iXlineEndSelect),   qMax(iXlineFirstSelect, iXlineEndSelect));
			//bool b4 = IsBound(iXlineEnd,    qMin(iXlineFirstSelect, iXlineEndSelect),   qMax(iXlineFirstSelect, iXlineEndSelect));
			//bool b5 = (iInlineIncSelect == iInlineInc);
			//bool b6 = (iXlineIncSelect == iXlineInc);

			bool b1 = qMin(iInlineStart, iInlineEnd) > qMax(iInlineFirstSelect, iInlineEndSelect);
			bool b2 = qMax(iInlineStart, iInlineEnd) < qMin(iInlineFirstSelect, iInlineEndSelect);
			bool b3 = qMin(iXlineStart, iXlineEnd) > qMax(iXlineFirstSelect, iXlineEndSelect);
			bool b4 = qMax(iXlineStart, iXlineEnd) < qMin(iXlineFirstSelect, iXlineEndSelect);

			//bool bMatched = (b1 && b2 && b3 && b4 && b5 && b6);

			if (!bX || !bY)	 // do not have X Y
			{
				if (!(b1 || b2 || b3 || b4))
				{
					_Create3DSurface(m_pSelectedUTM, m_pSelectedUTM, CXImport3DSurfaceManager::e_H_Line);
				}
				else
				{
					QMessageBox::warning(NULL, ::g_strProductName, "The selected survey does not lie in the same region with the selected data!");
					return false;
				}
			}
			else	 // have XY
			{
				CXSeismicUTMTool seismicUTM;
				m_pImportMgr->GuessUTMTool(&seismicUTM, m_bWithoutZone);

				if (seismicUTM.IsCompatible(m_pSelectedUTM))
				{
					_Create3DSurface(m_pSelectedUTM, &seismicUTM, CXImport3DSurfaceManager::e_H_Line_XY);
				}
				else
				{
					QMessageBox::warning(NULL, g_strProductName, "The data does not match the selected survey.");
					return false;
				}
			}
		}
		else // do not have inline (xline)
		{
			double dXMin, dXMax, dYMin, dYMax, dZMin, dZMax;
			double dXMinSelect, dXMaxSelect, dYMinSelect, dYMaxSelect;

			m_pImportMgr->GetXYZMinMax(0, dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
			m_pSelectedUTM->GetDimensionRange(dXMinSelect, dXMaxSelect, dYMinSelect, dYMaxSelect);
			bool bNotIntersect = (dXMin > dXMaxSelect || dXMax < dXMinSelect || dYMin > dYMaxSelect || dYMax < dYMinSelect);

			if (!bNotIntersect)	  // intersect
			{
				if (bI && bJ && bX && bY)   // have I, J, X and Y
				{
					CXUTMTool utm;
					m_pImportMgr->GuessUTMTool(&utm, m_bWithoutZone);

					_Create3DSurface(m_pSelectedUTM, &utm, CXImport3DSurfaceManager::e_H_IJ_XY);
				}
				else if (bX && bY)  // have X and Y
				{
					_Create3DSurface(m_pSelectedUTM, m_pSelectedUTM, CXImport3DSurfaceManager::e_H_XY);
				}
				else if (!bI && !bJ && !bX && !bY)  // only have data
				{
					CXUTMTool utm;
					m_pImportMgr->GetRegularUTMTool(&utm);
					_Create3DSurface(m_pSelectedUTM, &utm, CXImport3DSurfaceManager::e_H);
				}
			}
			else
			{
				QMessageBox::warning(NULL, g_strProductName, "The data does not match the selected survey.");
				return false;
			}
		}
	}
	else  // do not have selected UTM
	{
		if (bInline && bXline && !bX && !bY) // only have inline/xline
		{
			QMessageBox::warning(NULL, ::g_strProductName, "Please select one 3-D survey or select more column data!");
			return false;
		}
		else if (bInline && bXline && bX && bY)   //have inline/crossline and X/Y
		{
			CXSeismicUTMTool seismicUTM;
			m_pImportMgr->GuessUTMTool(&seismicUTM, m_bWithoutZone);
			_Create3DSurface(NULL, &seismicUTM, CXImport3DSurfaceManager::e_S_Line_XY);
		}
		else if (bI && bJ && bX && bY)   // have I, J, X and Y
		{
			CXUTMTool utm;
			m_pImportMgr->GuessUTMTool(&utm, m_bWithoutZone);
			_Create3DSurface(NULL, &utm, CXImport3DSurfaceManager::e_S_IJ_XY);
		}
		else if (!bInline && !bXline && !bI && !bJ && !bX && !bY) // do not have inline/crossline, X/Y, I/J
		{
			CXUTMTool utm;
			m_pImportMgr->GetRegularUTMTool(&utm, m_bWithoutZone);
			_Create3DSurface(NULL, &utm, CXImport3DSurfaceManager::e_S);
		}
		else
		{
			QMessageBox::warning(NULL, g_strProductName, "Please select one 3-D survey or select more column data!");
			return false;
		}

	}
	return true;
}

void CXFile3DSurface::_Create3DSurface(CXSeismicUTMTool* pSelectUTM, CXUTMTool* pUTM, int nDataType)
{
	m_listOutput.clear();

	//Get horizon info
	int nHorizonCount = m_pImportMgr->GetHorizonNum();
	QStringList strListHorizonName = m_pImportMgr->GetHorizonListName();

	for (int i = 0; i < nHorizonCount; ++i)
	{
		QString strName = strListHorizonName[i];
		CX3DSurface* pSurface = NULL;

		if (pSelectUTM)
		{
			pSurface = new CX3DHorizon(m_uuidSurvey, *m_pSelectedUTM, strName);
		}
		else
		{
			pSurface = new CX3DSurface(*pUTM, strName);
		}

		m_pImportMgr->ConvertColumnDataToSurface(pSurface, pUTM, i, nDataType);

		m_listOutput.append(pSurface);
	}
}

void CXFile3DSurface::SetSurveyInfo(CXSeismicUTMTool* pUTM, const QUuid& uuidSurvey)
{
	m_pSelectedUTM = pUTM;
	m_uuidSurvey = uuidSurvey;
}

void CXFile3DSurface::SetGeometrySurface(CX3DSurface * pGeometry)
{
	m_pGeometrySurface = pGeometry;
}
