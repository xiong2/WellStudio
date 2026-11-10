#include "xdataconvertor.h"
#include "xsegylineheader.h"

CXSEGYLineHeader::CXSEGYLineHeader(bool bCreate)
{
	memset(m_pBuff, 0, LINEHEADERLENGTH);
	
	if (bCreate)
	{
		int i;

		//	01~12
		int *pIVal = (int *)m_pBuff;
		pIVal[0] = 1;
		pIVal[1] = 1;
		pIVal[2] = 1;

		m_bNeedFlip = false;
	}
	else
	{
		m_bNeedFlip = true;
	}
}

//	Get the QStringList that consist of 32 items of line header.
QStringList CXSEGYLineHeader::GetItems()
{
	int i;
	QStringList strList;

	//	No.1, 2, 3 three integer.
	int* pInteger = new int[3];
	memcpy(pInteger, m_pBuff, 3 * sizeof(int));
	for(i = 0; i < 3; i++)
	{
		if(m_bNeedFlip)
			::Reverse(pInteger[i]);
		strList<<QString::number(pInteger[i]);
	}

	//	No.4 to 27, 24 shorts.
	short* pShort = new short[24];
	memcpy(pShort, m_pBuff + 3 * sizeof(int), 24 * sizeof(short));
	for(i = 0; i < 24; i++)
	{
		if(m_bNeedFlip)
			::Reverse(pShort[i]);
		strList<<QString::number(pShort[i]);
	}

	//	No.28, 240 bytes not used.
	strList<<"Unassigned";

	//	No.29 to 31, 3 short.
	memcpy(pShort, m_pBuff + 300, 3 * sizeof(short));
	for(i = 0; i < 3; i++)
	{
		if(m_bNeedFlip)
			::Reverse(pShort[i]);
		strList<<QString::number(pShort[i]);
	}

	//	No.32, 94 bytes not used.
	strList<<"Unassigned";

	delete []pInteger;
	delete []pShort;

	return strList;
}

//	Get sample interval from line header.
float CXSEGYLineHeader::GetSampleInterval()
{
	//	Sample interval locates at 17, 18 byte.
	short ss = *((short *)(m_pBuff + 16));

	if(m_bNeedFlip)
		::Reverse(ss);

	//	Since the unit is microsecond, we need millisecond, divid it by 1000.
	float fInterval;
	if (ss > 100)
	{
		ss /= 100;
		fInterval = (float)ss;
		fInterval /= 10.;
	}
	else
	{
		//	In case the unit is not microsecond.
		fInterval = (float)ss;
	}
	return fInterval;
}

//	Write sample interval to 3217, unit is ns.
void CXSEGYLineHeader::WriteSampleInterval(int iSampleInt)
{
	short *pSVal = (short *)(m_pBuff + 16);
	pSVal[0] = iSampleInt;
}

//	Get sample number of per trace.
unsigned short CXSEGYLineHeader::GetSampleNumber()
{
	//	Sample number locates at 21, 22 byte.
	unsigned short ss = *((short *)(m_pBuff + 20));

	if(m_bNeedFlip)
		::Reverse(ss);

	return ss;
}

//	Write sample number per trace to 3221.
void CXSEGYLineHeader::WriteSampleNumber(int iSampleInt)
{
	short *pSVal = (short *)(m_pBuff + 20);
	pSVal[0] = iSampleInt;
}

//	Get data type.
unsigned short CXSEGYLineHeader::GetDataType()
{
	//	Date type locates at 25, 26 byte.
	unsigned short ss = *((short *)(m_pBuff + 24));

	if(m_bNeedFlip)
		::Reverse(ss);

	//	1: 4-byte IBM float;	2: 4-byte integer;	3: 2-byte integer;	4: obsolete;	5: 4-byte IEEE float;	8: 1-byte integer.
	if(ss == 1)
		ss = 1;	//	IBM float.
	else if(ss == 2)
		ss = 2;	//	integer.
	else if(ss == 3)
		ss = 3;	//	short.
	else if(ss == 4)
		ss = 4;	//	Treat as char?
	else if(ss == 5)
		ss = 0;	//	IEEE float;
	else if(ss == 8)	
		ss = 4;	//	char.
	else
		ss = 5;	//	Error!

	return ss;
}

void CXSEGYLineHeader::WriteDataType(int iDataType)
{
	short *pSVal = (short *)(m_pBuff + 24);
	pSVal[0] = iDataType;
}

//	Get unit.
unsigned short CXSEGYLineHeader::GetUnit()
{
	//	Unit locates at 55,56 byte.
	unsigned short ss = *((short *)(m_pBuff + 54));

	if(m_bNeedFlip)
		::Reverse(ss);

	//	Only should be meter or foot, so 1 or 2.  If other value, set to 1 (meter).
	if(ss != 1 && ss != 2)
		ss = 1;

	return ss;
}

void CXSEGYLineHeader::WriteUnit(int iUnit)
{
	short *pSVal = (short *)(m_pBuff + 54);
	pSVal[0] = iUnit;
}

//	Initialize after set buff content, actually is guess whether need flip.
void CXSEGYLineHeader::Initialize()
{
	unsigned short iDataType = GetDataType();

	if(iDataType > 4)
		SetNeedFlip(false);

	float fSampleInterval = GetSampleInterval();
	if(fSampleInterval < 0.5 || fSampleInterval > 32.)
		SetNeedFlip(true);
}

void CXSEGYLineHeader::FlipBuff()
{
	int i;

	//	1~12, 3 integers.
	int *pIVal = (int *)m_pBuff;
	for (i = 0; i < 3; i++)
		Reverse(pIVal[i]);

	//	13~60, 24 shorts.
	short *pSVal = (short *)(m_pBuff + 12);
	for (i = 0; i < 24; i++)
		Reverse(pSVal[i]);

	//	301~306, 3 shorts.
	pSVal = (short *)(m_pBuff + 300);
	for (i = 0; i < 3; i++)
		Reverse(pSVal[i]);
}