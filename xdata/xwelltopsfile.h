#ifndef XWELLTOPSFILE_H__
#define XWELLTOPSFILE_H__

#include "xdata_global.h"
#include "xasciifile.h"

///@brief	Used to represent an ASCII well tops file being imported.
///@author	Xiong Xiong
///@date	Mar, 2014
///@see		
class XDATA_EXPORT CXWellTopsFile: public CXASCIIFile
{
public:
	CXWellTopsFile(QString sFile): CXASCIIFile(eWellTopsASCII, sFile)
	{
	}

	///@brief	Let derived classes to check the selected columns.
	virtual bool CheckSelectedColumns(QStringList&);

	virtual bool Import();

	QStringList	GetAllFormationsInFile();

	QStringList& GetSelectFormations()
	{
		return m_sListSelectedFormation;
	}

protected:
	QStringList	m_sListSelectedFormation;
};

#endif