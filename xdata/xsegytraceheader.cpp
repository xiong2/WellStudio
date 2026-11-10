#include "xdataconvertor.h"
#include "xsegytraceheader.h"
#include <qdebug.h>

CXSEGYTraceHeaderItem::CXSEGYTraceHeaderItem(CXSEGYTraceHeader *pTraceHeader, unsigned char iStartByte, unsigned char iLength, bool isFloat)
{
	m_pTraceHeader = pTraceHeader;
	m_iStartByte = iStartByte;
	m_iLength = iLength;

	if(iLength == 2)
		m_bIsFloat = false;
	else
		m_bIsFloat = isFloat;
}

double CXSEGYTraceHeaderItem::GetValue()
{
	float fVal = -999.;

	//	Invalid length.
	if(m_iLength != 2 && m_iLength != 4)
		return fVal;

	//	No original trace header or invalid position.
	if(!m_pTraceHeader || m_iStartByte + m_iLength > 240)
		return fVal;

	static char pBuff[16];
	memcpy(pBuff, m_pTraceHeader->GetOriginalTraceHeader() + m_iStartByte, m_iLength);

	//	Reverse it?  (note IBM float always need flip.)
	if(m_pTraceHeader->NeedFlip() || (m_bIsFloat && !m_pTraceHeader->IsIEEEFloat()))
		Reverse(pBuff, m_iLength);

	if(m_iLength == 2)
	{
		//	short.
		short sh = *((short *)pBuff);
		fVal = sh;
	}
	else if(!m_bIsFloat)
	{
		//	integer.
		int ii = *((int *)pBuff);
		//fVal = (float)ii;
		double dVal = static_cast<double>(ii);
		return dVal;
	}
	else if(m_pTraceHeader->IsIEEEFloat())
	{
		//	IEEE float.
		fVal = *((float *)pBuff);
	}
	else
	{
		//	IBM float.
		IBMToIEEE((int*)(pBuff), (int*)&fVal, 1);
	}

	return fVal;
}

bool CXSEGYTraceHeaderItem::IsFloat()
{
	//	2-bytes always be integer.
	if(m_iLength == 2)
		return false;
	else
		return m_bIsFloat;
}

//	Set to float, only works while length is 4-byte
void CXSEGYTraceHeaderItem::SetToFloat(bool bFloat)
{
	//	Can it be changed?
	if(m_iLength == 4)
		m_bIsFloat = bFloat;
	else
		m_bIsFloat = false;
}

//	Whether this element can be split to 2 items.
bool CXSEGYTraceHeaderItem::CanBeSplit()
{
	//	Only 4-byte item after 181 can be split!
	if(m_iLength == 4 && m_iStartByte >= 181)
		return true;
	else
		return false;
}

CXSEGYTraceHeader::CXSEGYTraceHeader()
{
	m_bIEEEFloat = true;
	m_bNeedFlip = true;

	CXSEGYTraceHeaderItem *pItem;
	
	unsigned char i, offset = 0;

	//	Default 7 integer, can change.
	for(i = 0; i < 7; i++)
	{
		pItem = new CXSEGYTraceHeaderItem(this, offset, 4, false);
		m_listItem.append(pItem);
		offset += 4;
	}

	//	followed 4 short, can not change.
	for(i = 0; i < 4; i++)
	{
		pItem = new CXSEGYTraceHeaderItem(this, offset, 2, false);
		m_listItem.append(pItem);
		offset += 2;
	}

	//	followed 8 integer, can change.
	for(i = 0; i < 8; i++)
	{
		pItem = new CXSEGYTraceHeaderItem(this, offset, 4, false);
		m_listItem.append(pItem);
		offset += 4;
	}

	//	followed 2 short, can not change.
	for(i = 0; i < 2; i++)
	{
		pItem = new CXSEGYTraceHeaderItem(this, offset, 2, false);
		m_listItem.append(pItem);
		offset += 2;
	}

	//	followed 4 integer, can change.
	for(i = 0; i < 4; i++)
	{
		pItem = new CXSEGYTraceHeaderItem(this, offset, 4, false);
		m_listItem.append(pItem);
		offset += 4;
	}

	//	followed 46 short, can not change.
	for(i = 0; i < 46; i++)
	{
		pItem = new CXSEGYTraceHeaderItem(this, offset, 2, false);
		qDebug() << "i is " << i << ", value is " << pItem->GetValue();
		m_listItem.append(pItem);
		offset += 2;
	}

	//	followed 15 integer, can change.
	for(i = 0; i < 15; i++)
	{
		pItem = new CXSEGYTraceHeaderItem(this, offset, 4, false);
		m_listItem.append(pItem);
		offset += 4;
	}
}

CXSEGYTraceHeader::~CXSEGYTraceHeader()
{
	freeMemory();
}

void CXSEGYTraceHeader::freeMemory()
{
	int count = m_listItem.count();
	for(int i = 0; i < count; i++)
	{
		CXSEGYTraceHeaderItem *pItem = m_listItem.at(i);
		delete pItem;
	}

	m_listItem.clear();
}

double CXSEGYTraceHeader::GetScaleFactor()
{
	CXSEGYTraceHeaderItem *pItem = m_listItem.at(20);

	double dVal = pItem->GetValue();

	if(dVal == 0. || dVal == 1. || dVal == -1.)
		dVal = 1.;

	if(dVal < 0)
	{
		dVal = -1./dVal;
	}

	return dVal;
}

//	Get the value of specified item.
float CXSEGYTraceHeader::GetValueAt(unsigned char ind)
{
	CXSEGYTraceHeaderItem *pItem = m_listItem.at(ind);
	return pItem->GetValue();
}