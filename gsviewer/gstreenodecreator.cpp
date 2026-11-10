#include "stdafx.h"
#include "gstreenodecreator.h"
#include "x3dsurvey.h"
#include "xgeneralfolder.h"
#include "gssection.h"
#include "gspdg.h"
#include "xtree.h"
#include <QPolygon>

GSSection* NGSTreeNodeCreator::CreateSection(CX3DSurvey* pSurvey, const QPolygonF& polyline)
{
	QList<CXObject*> listFolder = pSurvey->GetChildren(EXGSFolderSection, true);
	CXObject* pSectionFolder = nullptr;
	if (listFolder.isEmpty())
	{
		QList<CXObject*> listGSFolder = pSurvey->GetChildren(EXGSFolder, true);
		pSectionFolder = new CXGeneralFolder("Sections", EXGSFolderSection, "SectionFolder.png");
		listGSFolder.front()->AddChild(pSectionFolder);
	}
	else
	{
		pSectionFolder = listFolder.front();
	}

	auto pSection = new GSSection(pSurvey, pSectionFolder->GetUnallocatedName("Section"), polyline);
	pSectionFolder->AddChild(pSection);

	CXTree::Instance().AddOneObject(pSectionFolder);
	return pSection;
}

GSPDG* NGSTreeNodeCreator::CreatePDG(CX3DSurvey* pSurvey, const QPointF& point)
{
	QList<CXObject*> listFolder = pSurvey->GetChildren(EXGSFolderPDG, true);
	CXObject* pSectionFolder = nullptr;
	if (listFolder.isEmpty())
	{
		QList<CXObject*> listGSFolder = pSurvey->GetChildren(EXGSFolder, true);
		pSectionFolder = new CXGeneralFolder("PDGs", EXGSFolderPDG, "PDGFolder.png");
		listGSFolder.front()->AddChild(pSectionFolder);
	}
	else
	{
		pSectionFolder = listFolder.front();
	}

	auto pPDG = new GSPDG(pSurvey, pSectionFolder->GetUnallocatedName("PDG"), point);
	pSectionFolder->AddChild(pPDG);

	CXTree::Instance().AddOneObject(pSectionFolder);
	return pPDG;
}