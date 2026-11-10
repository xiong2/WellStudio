#pragma once
#include "xdata_global.h"
#include "xobject.h"

class XDATA_EXPORT CXFracturePatch : public CXObject
{
public:
	CXFracturePatch(QString sName = "");
	~CXFracturePatch();

	virtual QString GetTypeString() override { return "Fracture patches"; }

	virtual QStringList GetDescription() override;

	virtual bool SerializeData(CXArchive& ar) override;

	//	Each patch uses 12 + n doubles, 
	//	12 ones are the vertices of the quad patch, 
	//	other n are properties of that patch.
	void ResetData(QStringList, double* pData, unsigned int iNumber);

	QStringList GetProperties() { return m_sListProperties; }

protected:
	virtual void _SetSelfDimension() override;

	QStringList		m_sListProperties;		//	Name of the 3 properties.
};