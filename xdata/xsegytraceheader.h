#ifndef _CXSEGYTRACEHEADER_H__
#define _CXSEGYTRACEHEADER_H__

#include "xdata_global.h"
#include <QStringList>

#define TRACEHEADERLENGTH 240

class CXSEGYTraceHeader;

/**
*@brief		This class contain one element in the segy trace header.
*@author	Xiong Xiong
*@date		Apr, 2014
*/
class XDATA_EXPORT CXSEGYTraceHeaderItem
{
public:
	CXSEGYTraceHeaderItem(CXSEGYTraceHeader *, unsigned char startBype, unsigned char length, bool isFloat = false);

	///@brief	Get the value of this item.
	///@return	Though return value is float, it may should be cast to int or short.
	double GetValue();

	///@brief	Get the start byte.
	unsigned char GetStartByte()
	{
		return m_iStartByte;
	}

	///@brief	Get the length (Bytes)
	unsigned char GetLength()
	{
		return m_iLength;
	}

	///@brief	Is float?
	bool IsFloat();

	///@brief	Set to float, only works while length is 4-byte
	void SetToFloat(bool bFloat);

	///@brief	Whether this element can be split to 2 items.
	bool CanBeSplit();

private:
	unsigned char			m_iStartByte;		//	Start byte in CXSEGYTraceHeader's buff. 
	unsigned char			m_iLength;			//	Length of bytes, should be 1 or 2.
	bool					m_bIsFloat;			//	while m_iLength is 4, it can be float or integer.
	CXSEGYTraceHeader*		m_pTraceHeader;		//	Reference to CXSEGYTraceHeader.
};

/**
*@brief		This class contain one trace header in the segy file.
*@author	Xiong Xiong
*@date		Apr, 2014
*/
class XDATA_EXPORT CXSEGYTraceHeader
{
public:
	CXSEGYTraceHeader();
	~CXSEGYTraceHeader();

	///@brief	Get the 240 bytes original trace header.
	char* GetOriginalTraceHeader()
	{
		return m_pBuff;
	}

	///@brief	Set all float use IEEE or IBM format.
	void SetIEEEFloat(bool bIEEEFloat)
	{
		m_bIEEEFloat = bIEEEFloat;
	}

	///@brief	All float use IEEE or IBM forma?
	bool IsIEEEFloat()
	{
		return m_bIEEEFloat;
	}

	///@brief Set all elements need flip.
	void SetNeedFlip(bool bNeedFlip)
	{
		m_bNeedFlip = bNeedFlip;
	}

	///@brief	Do all elements need flip?
	bool NeedFlip()
	{
		return m_bNeedFlip;
	}

	///@brief	Get the scale factor from 71,72.
	double GetScaleFactor();
	
	///@brief	Get the value of specified item.
	float GetValueAt(unsigned char ind);

	///@brief	Get the specific item.
	CXSEGYTraceHeaderItem* GetItemAt(unsigned char ind)
	{
		return m_listItem.at(ind);
	}

	QList<CXSEGYTraceHeaderItem *>& GetAllItems()
	{
		return m_listItem;
	}

private:
	bool	m_bIEEEFloat;		//	Float may be IEEEE or IBM format.
	bool	m_bNeedFlip;		//	Need flip?
	char	m_pBuff[240];		//	Trace header in original format, not filp.

	QList<CXSEGYTraceHeaderItem *>	m_listItem;	//	List of item.

	void freeMemory();
};

#endif