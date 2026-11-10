#ifndef _CXWellPATHFILE_H__
#define _CXWellPATHFILE_H__

#include "xdata_global.h"
#include "xasciifile.h"

///@brief	Used to represent an ASCII well path file being imported.
///@author	Xiong Xiong
///@date	Mar, 2014
///@see		
class XDATA_EXPORT CXWellPathFile: public CXASCIIFile
{
public:
	CXWellPathFile(QString sFile): CXASCIIFile(eWellPathASCII, sFile)
	{
		m_iImportMode	= 0;
		m_bNegateZ		= false;
		m_bSimplifyData = false;
	}

	virtual bool Import();

	void SetImportMode(unsigned int iImportMode);

	void SetNegateZ(bool bNegateZ)
	{
		m_bNegateZ = bNegateZ;
	}

	void SetSimplify(bool bSimplify)
	{
		m_bSimplifyData = bSimplify;
	}

protected:
	unsigned int	m_iImportMode;	//	0 by MD, INc, Azi; 1 by TVD, DX, DY; 2 by TVD, X, Y; 3 by X, Y, Z; 4 by DX, DY, DZ
	bool			m_bNegateZ;		//	Whether negate all imported Z value.
	bool			m_bSimplifyData;	
};

#endif