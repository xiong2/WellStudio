#ifndef XFILE3DSURFACE_H
#define XFILE3DSURFACE_H

#include <qstring.h>
#include <qlist.h>
#include "xgui_global.h"
#include "xasciifile.h"

class CXImport3DSurfaceManager;
class CXUTMTool;
class CXSeismicUTMTool;
class CX3DSurface;
class QWidget;

///@brief	The class provides interface to import 3-D surfaces
///@author	Yong Shu
///@date	Apr. 10th, 2014
///@see	

class XGUI_EXPORT CXFile3DSurface: public CXASCIIFile
{
public:
	CXFile3DSurface(EImportFileType eFileType, const QString& strFileName = "");
	~CXFile3DSurface();

	///@brief Reimplementation
	virtual bool Import();

	///@brief Set and get the flag that indicates negating Z
	void SetNegateZ(bool bNegateZ) {m_bNegateZ = bNegateZ;}
	bool GetNegateZ() {return m_bNegateZ;}

	void SetWithoutZone(bool bWZ) {m_bWithoutZone = bWZ;}

	///@brief Set another file
	bool SetAdditionalFile(const QString& strFileName);

	///@brief Get the surface manager
	CXImport3DSurfaceManager* GetImSurManager() {return m_pImportMgr;}

	///@breif Set the selected UTM
	void SetSurveyInfo(CXSeismicUTMTool* pUTM, const QUuid& uuidSurvey);

	///@breif Set the geometry
	void SetGeometrySurface(CX3DSurface* pGeometry);

	///@brief Parse surface data
	bool ParseData();

	bool CheckSelectedColumns(QStringList&) override;

private:
	bool _CreateObj();
	void _Create3DSurface(CXSeismicUTMTool* pSelectUTM, CXUTMTool* pUTM, int nDataType);
		

private:
	bool m_bNegateZ;
	bool m_bWithoutZone;

	CXImport3DSurfaceManager* m_pImportMgr;

	CXSeismicUTMTool* m_pSelectedUTM;

	QUuid m_uuidSurvey;

	QList<CX3DSurface*> m_listOutput;

	CX3DSurface* m_pGeometrySurface;

private:
	QWidget* m_pParentWidget;

};

#endif // RLFILE3DSURFACE_H
