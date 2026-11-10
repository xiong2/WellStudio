#pragma once
#include "xasciifile.h"

class XDATA_EXPORT CXWellCheckShotFile : public CXASCIIFile
{
public:
	CXWellCheckShotFile(QString sFile) : CXASCIIFile(eWellCheckShot, sFile)
	{
	}

	virtual bool CheckSelectedColumns(QStringList&) override;

	virtual bool Import() override;

	void SetNegateZ(bool bNegateZ)
	{
		m_bNegateZ = bNegateZ;
	}

protected:
	bool			m_bNegateZ;		//	Whether negate all imported Z value.
};