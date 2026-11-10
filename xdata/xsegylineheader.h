#ifndef _CXSEGYLINEHEADER_H__
#define _CXSEGYLINEHEADER_H__

#include "xdata_global.h"
#include <QStringList>

#define LINEHEADERLENGTH 400

/**
*@brief		This class contains one line header of a segy file.
*@author	Xiong Xiong
*@date		Apr, 2014
*/
class XDATA_EXPORT CXSEGYLineHeader
{
public:
	CXSEGYLineHeader(bool bCreate = false);

	///@brief	Get the QStringList that consist of 32 items of line header.
	QStringList GetItems();

	///@brief	Need flip?
	bool GetNeedFlip()
	{
		return m_bNeedFlip;
	}

	///@brief	Set whether need flip.
	void SetNeedFlip(bool bFlip)
	{
		m_bNeedFlip = bFlip;
	}

	///@brief	Get the original line header buff.
	char* GetLineHeaderBuff()
	{
		return m_pBuff;
	}

	///@brief	Get sample interval from line header 3217.
	float GetSampleInterval();

	///@brief	Write sample interval to 3217, unit is ns.
	void WriteSampleInterval(int);

	///@brief	Get sample number of per trace from 3221.
	unsigned short GetSampleNumber();

	///@brief	Write sample number per trace to 3221.
	void WriteSampleNumber(int);

	///@brief	Get data type from 3225.
	unsigned short GetDataType();

	///@brief	Write data type to 3225.
	void WriteDataType(int);

	///@brief	Get unit from 3255.
	unsigned short GetUnit();

	///@brief	Write unit to 3255.
	void WriteUnit(int);

	///@brief	Initialize, should be call after set buff content.
	void Initialize();

	void FlipBuff();

private:
	char			m_pBuff[LINEHEADERLENGTH];	//	Original 400 bytes line header.
	bool			m_bNeedFlip;				//	Need flip?
};

#endif