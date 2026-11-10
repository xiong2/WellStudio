#include <qdebug.h>
#include "xdlisparser.h"
#include "xwell.h"
#include "xwellcurve.h"
#include "xwellnmr.h"
#include "xunit.h"
#include "xglobal.h"
#include "xproject.h"

CXDLISCD::CXDLISCD(unsigned char *pCh): m_pCh(pCh)
{
	m_iType = -1;

	int iValue = pCh[0] & 0xe0;
	if (iValue == 0x0)
		m_iType = 0;	//	Absent Attribute
	else if (iValue == 0x20)
		m_iType = 1;	//	Attribute
	else if (iValue == 0x40)
		m_iType = 2;	//	Invariant Attribute
	else if (iValue == 0x60)
		m_iType = 3;	//	Object
	else if (iValue == 0xa0)
		m_iType = 4;	//	Redundant Set
	else if (iValue == 0xc0)
		m_iType = 5;	//	Replacement Set
	else if (iValue == 0xe0)
		m_iType = 6;	//	Set
}

bool CXDLISCD::Contains(int iSymbol)
{
	if (m_iType == 1 || m_iType == 2)
	{
		if (iSymbol == 0)
			return (*m_pCh) & 0x10;
		else if (iSymbol == 1)
			return (*m_pCh) & 0x8;
		else if (iSymbol == 2)
			return (*m_pCh) & 0x4;
		else if (iSymbol == 3)
			return (*m_pCh) & 0x2;
		else if (iSymbol == 4)
			return (*m_pCh) & 0x1;
	}
	else if (m_iType == 3)
	{
		if (iSymbol == 0)
			return (*m_pCh) & 0x10;
	}
	else if (m_iType == 4 || m_iType == 5 || m_iType == 6)
	{
		if (iSymbol == 0)
			return (*m_pCh) & 0x10;
		if (iSymbol == 1)
			return (*m_pCh) & 0x8;
	}

	return false;
}

CXDLISParser::CXDLISParser(QString sFileName)
{
	m_strWellName = "";

	QString sOutFile = sFileName;
	sOutFile.replace(".dlis", ".txt");

	m_qDLISFile.setFileName(sFileName);
	m_qTXTFile.setFileName(sOutFile);
}

CXDLISParser::~CXDLISParser()
{
	if (m_qDLISFile.isOpen())
		m_qDLISFile.close();

	if (m_qTXTFile.isOpen())
		m_qTXTFile.close();

	foreach(CXDLISFrame *pFrame, m_vecFrame)
		delete pFrame;
}

bool CXDLISParser::Parse()
{
	//	Source DLIS file.
	if (!m_qDLISFile.open(QIODevice::ReadOnly))
	{
		qDebug() << "Can not open the DLIS file to read!";
		return false;
	}
	qint64 iFileSize = m_qDLISFile.size();

	//	Tmp output file.
	if (!m_qTXTFile.open(QIODevice::WriteOnly))
	{
		qDebug() << "Can not open the text file to write!";
		m_qTXTFile.close();
		return false;
	}
	m_stream.setDevice(&m_qTXTFile);

	char *pBuffer = new char[4096];
	unsigned short *pShort = (unsigned short *)pBuffer;
	char pTmp[1024];

	//	First check whether it's a DLIS version 1 file.
	m_qDLISFile.read(pBuffer, 80);
	memcpy(pTmp, pBuffer + 4, 5);
	QString sVer = QString(pTmp);
	if (sVer != "V1.00")
	{
		qDebug() << "It's not a DLIS version 1 file!";
		delete[]pBuffer;
		m_qDLISFile.close();
		m_qTXTFile.close();

		return false;
	}

	//	Current visible record length and the start position of next visible record.
	readVRHeader();

	bool bFirstIFRL = true;
	QVector<SKEDLISLR>	vecLR;

	//	Now we want to read through the file to check all the LRSH (Logical Record Segment Header)
	while (m_qDLISFile.pos() < iFileSize)
	{
		//	Just the VR header, skip it.
		if (m_qDLISFile.pos() == m_iNextVRPos)
			readVRHeader();

		//	Read in a LRSH.
		m_qDLISFile.read(pBuffer, 4);
		flipShort(pBuffer);
		m_iCurLRSLen = pShort[0];
		m_iNextLRSPos = m_qDLISFile.pos() + m_iCurLRSLen - 4;

		//	Write the segment type into output file.
		unsigned char ch1 = pBuffer[2];
		unsigned char ch2 = pBuffer[3];
		QString s0 = "00000000";
		QString s1 = QString::number(ch1, 2);
		s0.replace(s0.length() - s1.length(), s1.length(), s1);
		QString sSegmentAtt = "IFLR: " + s0;
		if (ch1 & 0x80)
			sSegmentAtt = "EFLR: " + s0;
		m_stream << sSegmentAtt << "		" << QString::number(ch2) << "		" << QString::number(m_iCurLRSLen) << endl;

		bool bFirst = !(ch1 & 0x40);	//	The first segment of the LR.
		bool bLast = !(ch1 & 0x20);	//	The Last segment of the LR.

		SKEDLISLR sLR;
		sLR.m_iStartPos = m_qDLISFile.pos();
		sLR.m_iLength = m_iCurLRSLen - 4;
		if (ch1 & 0x2)					//	Has trailing length
			sLR.m_iLength -= 2;
		if (ch1 & 0x4)					//	Has checksum
			sLR.m_iLength -= 2;

		if (ch1 & 0x80)
		{
			//	It's an EFLR record.
			if (ch2 > 11)
			{
				m_stream << "The undefined or private EFLR need not read so far!" << endl;
				m_stream << endl;

				m_qDLISFile.seek(m_iNextLRSPos);
				continue;
			}

			if (ch2 != 1 && ch2 != 3 && ch2 != 4)
			{
				m_stream << "So far only output OLR, CHANNL and FRAME!" << endl;
				m_stream << endl;

				m_qDLISFile.seek(m_iNextLRSPos);
				continue;
			}

			vecLR << sLR;

			if (bLast)
			{
				//	Haddle the EFLR, we first combine all segments to one buffer.
				unsigned int iTotalLen = 0;
				foreach(SKEDLISLR sEFLR, vecLR)
				{
					iTotalLen += sEFLR.m_iLength;
				}

				char *pEFLRBuff = new char[iTotalLen];
				char *pCurBuff = pEFLRBuff;
				foreach(SKEDLISLR sEFLR, vecLR)
				{
					m_qDLISFile.seek(sEFLR.m_iStartPos);
					m_qDLISFile.read(pCurBuff, sEFLR.m_iLength);
					pCurBuff += sEFLR.m_iLength;
				}

				//	Then parse the buffer.
				parseEFLR((unsigned char *)pEFLRBuff, iTotalLen, ch2);

				//	Free the memory.
				delete[]pEFLRBuff;
				vecLR.clear();
			}

		}
		else
		{
			vecLR << sLR;

			//	It's an IFLR record.
			if (bFirstIFRL)
			{
				//	That mean all EFRL be read, let's do some statistic here.
				sortChannels();

				int iNumSlot = 0, iC = 0;
				foreach(CXDLISFrame *pFrame, m_vecFrame)
				{
					int iNumFSlot = 0;
					foreach(CXDLISChannel *pChannel, pFrame->m_vecChannel)
					{
						iNumFSlot += pChannel->m_iDimension;
						iC++;
					}

					m_stream << "Frame slots is " << QString::number(iNumFSlot) << endl;
					iNumSlot += iNumFSlot;
				}
				m_stream << "Well name is " << m_strWellName << endl;
				m_stream << "------------------ Total slots number is " << QString::number(iNumSlot) << "-----------------" << endl;
				m_stream << endl;

				bFirstIFRL = false;
			}

			if (bLast)
			{
				//	Haddle the IFLR, we first combine all segments to one buffer.
				unsigned int iTotalLen = 0;
				foreach(SKEDLISLR sIFLR, vecLR)
				{
					iTotalLen += sIFLR.m_iLength;
				}

				char *pIFLRBuff = new char[iTotalLen];
				char *pCurBuff = pIFLRBuff;
				for(SKEDLISLR sIFLR : vecLR)
				{
					m_qDLISFile.seek(sIFLR.m_iStartPos);
					m_qDLISFile.read(pCurBuff, sIFLR.m_iLength);
					pCurBuff += sIFLR.m_iLength;
				}

				//	Then parse the buffer.
				parseIFLR((unsigned char *)pIFLRBuff, iTotalLen);

				//	Free the memory.
				delete[]pIFLRBuff;
				vecLR.clear();
			}
		}

		m_qDLISFile.seek(m_iNextLRSPos);
	}

	delete[]pBuffer;
	return true;
}

void CXDLISParser::PopulateCurvesAndUnits(QStringList& sListCurves, QStringList& sListUnits)
{
	foreach(CXDLISFrame *pFrame, m_vecFrame)
	{
		foreach(CXDLISChannel *pCh, pFrame->m_vecChannel)
		{
			sListCurves << pCh->m_sName;
			sListUnits << pCh->m_sUnit;
		}
	}
}

void CXDLISParser::PopulateWellRange(float& fSDepth, float& fEDepth, float& fDepthStep)
{
	fSDepth = 9999999.;
	fEDepth = -9999999.;
	fDepthStep = 9999999.;

	foreach(CXDLISFrame *pFrame, m_vecFrame)
	{
		if (fSDepth > pFrame->m_fSDepth)
			fSDepth = pFrame->m_fSDepth;
		if (fEDepth < pFrame->m_fEDepth)
			fEDepth = pFrame->m_fEDepth;
		if (fDepthStep > qAbs(pFrame->m_fSpacing))
			fDepthStep = qAbs(pFrame->m_fSpacing);
	}
}

bool CXDLISParser::LoadCurves(CXWell *pWell, QStringList& sListCurves, QList<CXObject *>& listObj)
{
	foreach(CXDLISFrame *pFrame, m_vecFrame)
	{
		foreach(CXDLISChannel *pCh, pFrame->m_vecChannel)
		{
			//	Abort the curves not selected by user.
			if (!sListCurves.contains(pCh->m_sName))
				continue;

			if (pCh->m_iDimension == 1)
			{
				//	One dimension curve.
				CXWellCurve *pCurve = new CXWellCurve(pCh->m_sName);
				pCurve->ResetData(pFrame->m_fSDepth, qAbs(pFrame->m_fSpacing), pFrame->m_iNumSamples, pCh->m_pBuffer);
				pCh->m_pBuffer = NULL;

				pWell->AddChild(pCurve);
				listObj.append(pCurve);
			}
			else
			{
				CXObject *pFolder = pWell->GetFolder(EXNMRFolder, true);
				CXWellNMR *pNMR = new CXWellNMR(pFrame->m_fSDepth, qAbs(pFrame->m_fSpacing), pFrame->m_iNumSamples, 1, 1, pCh->m_iDimension, pCh->m_sName);
				pFolder->AddChild(pNMR);

				int iIDX = 0, iIDX1, iIDX2;
				float *pData = pNMR->GetDataCache();
				for (iIDX1 = 0; iIDX1 < pFrame->m_iNumSamples; iIDX1++)
				{
					for (iIDX2 = 0; iIDX2 < pCh->m_iDimension; iIDX2++)
					{
						if (pCh->m_pBuffer[iIDX2 * pFrame->m_iNumSamples + iIDX1] == -999.)
							pData[iIDX2] = ::g_dInvalidData;
						else
							pData[iIDX2] = pCh->m_pBuffer[iIDX2 * pFrame->m_iNumSamples + iIDX1];

						iIDX++;
					}

					pNMR->WriteTraceData(iIDX1);
				}

				pNMR->CloseFile();
				pNMR->SetModifiedFlag();
				::AddObjectEvent(pNMR);

				listObj.append(pNMR);
			}
		}
	}
		
	return true;
}

void CXDLISParser::sortChannels()
{
	QString sDepthUnit = "m";
	if (!::GetProject()->UsingMetricUnit())
		sDepthUnit = "ft";

	foreach (CXDLISFrame *pFrame, m_vecFrame)
	{
		pFrame->m_iNumSamples = (int)(qAbs((pFrame->m_fEDepth - pFrame->m_fSDepth) / pFrame->m_fSpacing) + 0.99) + 1;
		double dRatio = CXUnit::GetConvertRatio(pFrame->m_sDepthUnit, sDepthUnit);
		pFrame->m_fSDepth *= dRatio;
		pFrame->m_fEDepth *= dRatio;
		pFrame->m_fSpacing *= dRatio;

		foreach(QString sChannelName, pFrame->m_listChannel)
		{
			foreach(CXDLISChannel *pChannel, m_vecChannel)
			{
				if (pChannel->m_sName == sChannelName)
				{
					CXDLISChannel *pNewChannel = new CXDLISChannel(sChannelName);
					pNewChannel->m_sDesp = pChannel->m_sDesp;
					pNewChannel->m_sUnit = pChannel->m_sUnit;
					pNewChannel->m_iDimension = pChannel->m_iDimension;
					pNewChannel->m_iRepCode = pChannel->m_iRepCode;
					pNewChannel->m_pBuffer = new double[pNewChannel->m_iDimension * pFrame->m_iNumSamples];
					pFrame->m_vecChannel << pNewChannel;
					break;
				}
			}
		}
	}

	//	Now the vector of channels no longer needed.
	foreach(CXDLISChannel *pChannel, m_vecChannel)
		delete pChannel;
	m_vecChannel.clear();
}

float CXDLISParser::readFSINGL(unsigned char *& pCh)
{
	float *pF = (float *)pCh;
	flip4Bytes((char *)pCh);

	pCh += 4;
	return pF[0];
}

short CXDLISParser::readSNORM(unsigned char *& pCh)
{
	short *pSh = (short *)pCh;
	flipShort((char *)pCh);

	pCh += 2;
	return pSh[0];
}

int CXDLISParser::readSLONG(unsigned char *& pCh)
{
	int *pI = (int *)pCh;
	flip4Bytes((char *)pCh);

	pCh += 4;
	return pI[0];
}

unsigned int CXDLISParser::readULONG(unsigned char *& pCh)
{
	unsigned int *pI = (unsigned int *)pCh;
	flip4Bytes((char *)pCh);

	pCh += 4;
	return pI[0];
}

unsigned short CXDLISParser::readUNORM(unsigned char *& pCh)
{
	unsigned short *pSh = (unsigned short *)pCh;
	flipShort((char *)pCh);

	pCh += 2;
	return pSh[0];
}

unsigned int CXDLISParser::readUVARI(unsigned char *& pCh)
{
	if ((*pCh & 0x80) == 0)
	{
		//	1 byte.
		unsigned int iValue = *pCh;

		pCh++;
		return iValue;
	}
	else if ((*pCh & 0x40) == 0)
	{
		//	2 bytes.
		unsigned short *pSh = (unsigned short *)pCh;
		pCh[0] &= 0x3F;
		flipShort((char *)pCh);
		
		pCh += 2;
		return pSh[0];
	}
	else
	{
		//	4 bytes.
		unsigned int *pInt = (unsigned int *)pCh;
		pInt[0] &= 0x3F;
		flip4Bytes((char *)pCh);

		pCh += 4;
		return pInt[0];
	}
}

QString CXDLISParser::readIDENT(unsigned char *& pCh)
{
	unsigned int iLen = *pCh;
	pCh++;

	QString str = QString::fromLatin1((char *)pCh, iLen);
	pCh += iLen;

	return str;
}

QString CXDLISParser::readASCII(unsigned char *& pCh)
{
	unsigned int iLen = readUVARI(pCh);

	QString str = QString::fromLatin1((char *)pCh, iLen);
	pCh += iLen;

	return str;
}

QString CXDLISParser::readDTIME(unsigned char *& pCh)
{
	pCh += 8;

	return QString("YYYYMMDD");
}

QString CXDLISParser::readOBNAME(unsigned char *& pCh)
{
	unsigned int iOri = readUVARI(pCh);
	unsigned int iCopy = *pCh;
	pCh++;

	QString sID = readIDENT(pCh);

	return QString::number(iOri) + "&" + QString::number(iCopy) + "&" + sID;
}

QString CXDLISParser::readOBJREF(unsigned char *& pCh)
{
	QString sType = readIDENT(pCh);
	QString sObjName = readOBNAME(pCh);
	return sType + "+" + sObjName;
}

QString CXDLISParser::readRepCode(unsigned char *& pCh, unsigned char repCode)
{
	QString str = "";

	if (repCode == 2)
	{
		str = QString::number(readFSINGL(pCh));
	}
	else if (repCode == 13)
	{
		str = QString::number(readSNORM(pCh));
	}
	else if (repCode == 14)
	{
		str = QString::number(readSLONG(pCh));
	}
	else if (repCode == 15 || repCode == 26)
	{
		unsigned int iValue = *pCh;
		str = QString::number(iValue);
		pCh++;
	}
	else if (repCode == 16)
	{
		str = QString::number(readUNORM(pCh));
	}
	else if (repCode == 17)
	{
		str = QString::number(readULONG(pCh));
	}
	else if (repCode == 18 || repCode == 22)
	{
		str = QString::number(readUVARI(pCh));
	}
	else if (repCode == 19 || repCode == 27)
	{
		str = readIDENT(pCh);
	}
	else if (repCode == 20)
	{
		str = readASCII(pCh);
	}
	else if (repCode == 21)
	{
		str = readDTIME(pCh);
	}
	else if (repCode == 23)
	{
		str = readOBNAME(pCh);
	}
	else if (repCode == 24)
	{
		str = readOBJREF(pCh);
	}
	else
	{
		qDebug() << "RepCode " << QString::number(repCode) << " not implemented it yet!";
	}

	return str;
}

void CXDLISParser::flipShort(char *pSh, int iNum)
{
	for (int i = 0; i < iNum; i++)
	{
		char ch = pSh[2 * i];
		pSh[2 * i] = pSh[2 * i + 1];
		pSh[2 * i + 1] = ch;
	}
}

void CXDLISParser::flip4Bytes(char *pCh, int iNum)
{
	for (int i = 0; i < iNum; i++)
	{
		char ch = pCh[4 * i];
		pCh[4 * i] = pCh[4 * i + 3];
		pCh[4 * i + 3] = ch;

		ch = pCh[4 * i + 1];
		pCh[4 * i + 1] = pCh[4 * i + 2];
		pCh[4 * i + 2] = ch;
	}
}

void CXDLISParser::readVRHeader()
{
	char pBuff[4];
	unsigned short *pShort = (unsigned short *)pBuff;

	m_qDLISFile.read(pBuff, 4);
	flipShort(pBuff);
	m_iCurVRLen = pShort[0];
	m_iNextVRPos = m_qDLISFile.pos() + m_iCurVRLen - 4;
}

bool CXDLISParser::parseIFLR(unsigned char *pBuff, int iLength)
{
	unsigned char *pOri = pBuff;
	unsigned char *pEnd = pOri + iLength;
	CXDLISFrame *pCurFrame = NULL;

	QString sObjName = readOBNAME(pBuff);
	unsigned int iFrameNumber = readUVARI(pBuff);

	m_stream << "Obj name is " << sObjName << ", Frame number is " << QString::number(iFrameNumber) << endl;
	
	//	Now find the frame this IFLR for.
	foreach(CXDLISFrame *pFrame, m_vecFrame)
	{
		if (pFrame->m_sObjName == sObjName)
		{
			pCurFrame = pFrame;
			break;
		}
	}

	if (!pCurFrame)
	{
		m_stream << "Frame name is " << sObjName << ", not found in vector!" << endl;
		return false;
	}

	if (iFrameNumber == 0 || iFrameNumber > pCurFrame->m_iNumSamples)
	{
		m_stream << "Frame name is out of range!" << endl;
		return true;
	}

	//	Now find the data offset this frame locates.
	unsigned int iOffset = iFrameNumber - 1;
	if (pCurFrame->m_fSpacing < 0)
		iOffset = pCurFrame->m_iNumSamples - iFrameNumber;

	//	Now loop each channel of this frame.
	foreach(CXDLISChannel *pChannel, pCurFrame->m_vecChannel)
	{
		unsigned int iChOffset = iOffset * pChannel->m_iDimension;
		for (int i = 0; i < pChannel->m_iDimension; i++)
			pChannel->m_pBuffer[iChOffset + i] = (double)readRepCode(pBuff, pChannel->m_iRepCode).toFloat();
	}

	return true;
}

bool CXDLISParser::parseEFLR(unsigned char *pBuff, int iLength, unsigned char iType)
{
	unsigned char *pOri = pBuff;
	unsigned char *pEnd = pOri + iLength;

	//	Whether this LR is for ORIGIN.
	bool bOrigin = (iType == 1);
	int iWellNameIDX = 999;

	//	Whether this LR is for CHANNEL.
	bool bChannel = (iType == 3);
	int iDespIDX = 999;
	int iDimensionIDX = 999;
	int iUnitIDX = 999;
	int iRepCodeIDX = 999;
	CXDLISChannel *pChannel = NULL;
	if(!m_vecChannel.isEmpty())
		pChannel = m_vecChannel.last();

	//	Whether this LR is FRAME.
	bool bFrame = (iType == 4);
	int iChannelsIDX = 999;
	int iIndexMaxIDX = 999;
	int iIndexMinIDX = 999;
	int iSpacingIDX = 999;
	CXDLISFrame *pFrame = NULL;
	if (!m_vecFrame.isEmpty())
		pFrame = NULL;

	//	1 byte CD.
	CXDLISCD cd(pBuff);
	pBuff++;

	//	First component should be "set".
	if (cd.GetType() != 6)
	{
		m_stream << "The first component of an EFLR is not set!" << endl;

		delete[]pOri;
		return false;
	}

	QString sSetStr = "Set: ";
	if (cd.Contains(0))
	{
		//	Set type.
		QString sSetType = readIDENT(pBuff);

		sSetStr += "type is " + sSetType + ". ";
	}
	if (cd.Contains(1))
	{
		//	Set name.
		QString sSetName = readIDENT(pBuff);
		sSetStr += "name is " + sSetName + ". ";
	}
	m_stream << sSetStr << endl;

	bool bTempAtt = true;
	unsigned int iAttIDX = 0;
	QVector<unsigned char> vecRepCode;

	//	Loop to read other CD.
	while (pBuff < pEnd)
	{
		CXDLISCD cd(pBuff);
		pBuff++;

		if (cd.GetType() == 1 || cd.GetType() == 2)
		{
			//	Attribute, it's template's attribute or object's?
			if (bTempAtt)
			{
				//	Template attribute.
				QString sAttr = "Template Attribute:";
				unsigned char iRC = 0x13;	//	Default representation code is IDENT.
				if (cd.Contains(0))
				{
					//	Attribute Label.
					QString sLabel = readIDENT(pBuff);
					sAttr = sAttr + " Label: " + sLabel;

					if (bOrigin)
					{
						if (sLabel == "WELL-NAME")
							iWellNameIDX = iAttIDX;
					}
					else if (bChannel)
					{
						if (sLabel == "LONG-NAME")
							iDespIDX = iAttIDX;
						else if (sLabel == "DIMENSION")
							iDimensionIDX = iAttIDX;
						else if (sLabel == "UNITS")
							iUnitIDX = iAttIDX;
						else if (sLabel == "REPRESENTATION-CODE")
							iRepCodeIDX = iAttIDX;
					}
					else if (bFrame)
					{
						if (sLabel == "CHANNELS")
							iChannelsIDX = iAttIDX;
						else if (sLabel == "INDEX-MAX")
							iIndexMaxIDX = iAttIDX;
						else if (sLabel == "INDEX-MIN")
							iIndexMinIDX = iAttIDX;
						else if (sLabel == "SPACING")
							iSpacingIDX = iAttIDX;
					}
				}
				if (cd.Contains(1))
				{
					//	Attribute Count.
					unsigned int iCount = readUVARI(pBuff);
					sAttr = sAttr + " Count: " + QString::number(iCount);
				}
				if (cd.Contains(2))
				{
					//	Attribute Representation Code.
					iRC = *(pBuff);
					pBuff++;
					sAttr = sAttr + " Rep-Code: " + QString::number(iRC);
				}
				else
				{
					//	No rep code, use default one.
					sAttr = sAttr + " Rep-Code: " + QString::number(iRC) + " (default)";
				}
				if (cd.Contains(3))
				{
					//	Attribute Units.
					sAttr = sAttr + " Units: " + readIDENT(pBuff);
				}
				if (cd.Contains(4))
				{
					//	Attribute value.
					sAttr = sAttr + " Value: " + readRepCode(pBuff, iRC);
				}

				iAttIDX++;
				m_stream << sAttr << endl;
				vecRepCode << iRC;
			}
			else
			{
				//	Object attribute.
				if (iAttIDX >= vecRepCode.size())
				{
					m_stream << "Attribute indices too big! May meet the end of LR!" << endl;
					break;
				}

				QString sAttr = "Object Attribute:", sValue, sUnit;
				unsigned int iCount = 1;
				unsigned char iRC = 0xff;
				if (cd.Contains(0))
				{
					//	Attribute Label.
					sAttr = sAttr + " Label: " + readIDENT(pBuff);
				}
				if (cd.Contains(1))
				{
					//	Attribute Count.
					iCount = readUVARI(pBuff);
					sAttr = sAttr + " Count: " + QString::number(iCount);
				}
				if (cd.Contains(2))
				{
					//	Attribute Representation Code.
					iRC = *(pBuff);
					pBuff++;
					sAttr = sAttr + " Rep-Code: " + QString::number(iRC);
				}
				if (cd.Contains(3))
				{
					//	Attribute Units.
					sUnit = readIDENT(pBuff);
					sAttr = sAttr + " Units: " + sUnit;
				}
				if (cd.Contains(4))
				{
					//	Attribute value.
					sAttr = sAttr + " Value: ";
					if (iRC == 0xff)
					{
						iRC = vecRepCode[iAttIDX];
					}

					for (int i = 0; i < iCount; i++)
					{
						sValue = readRepCode(pBuff, iRC);
						sAttr = sAttr + sValue + " ";

						if (bChannel && iAttIDX == iDimensionIDX)
						{
							pChannel->m_iDimension *= sValue.toInt();
						}

						if (bFrame && iAttIDX == iChannelsIDX)
						{
							int iPos = sValue.lastIndexOf("&");
							QString sName = sValue.right(sValue.length() - iPos - 1);
							pFrame->m_listChannel << sName;
						}
					}
				}

				//	For origin object.
				if (bOrigin)
				{
					if (iAttIDX == iWellNameIDX && sValue != "")
						m_strWellName = sValue;
				}

				//	For channel object.
				if (bChannel && pChannel)
				{
					if (iAttIDX == iDespIDX)
						pChannel->m_sDesp = sValue;
					else if (iAttIDX == iUnitIDX)
						pChannel->m_sUnit = sValue;
					else if (iAttIDX == iRepCodeIDX)
						pChannel->m_iRepCode = sValue.toUShort();
				}

				//	For Frame object.
				if (bFrame && pFrame)
				{
					if (iAttIDX == iIndexMaxIDX)
					{
						pFrame->m_fEDepth = sValue.toFloat();
					}
					else if (iAttIDX == iIndexMinIDX)
					{
						pFrame->m_fSDepth = sValue.toFloat();
					}
					else if (iAttIDX == iSpacingIDX)
					{
						pFrame->m_fSpacing = sValue.toFloat();
						pFrame->m_sDepthUnit = sUnit;
					}
				}

				iAttIDX++;
				m_stream << sAttr << endl;
			}
		}
		else if (cd.GetType() == 0)
		{
			//	Absent attribute.
			if (bTempAtt)
			{
				m_stream << "Someting error!  Absent attribute in template!" << endl;
				break;
			}
			else
			{
				iAttIDX++;
				m_stream << "Object Attribute: \"\"" << endl;
			}
		}
		else if (cd.GetType() == 3)
		{
			//	Object.
			iAttIDX = 0;
			bTempAtt = false;

			QString sName = "";
			if (cd.Contains(0))
			{
				//	Object Name.
				sName = readOBNAME(pBuff);
				m_stream << "Object name is " << sName << endl;
			}
			else
				m_stream << "Here is an anonymous object!" << endl;


			//	For channel object.
			if (bChannel)
			{
				int iPos = sName.lastIndexOf("&");
				sName = sName.right(sName.length() - iPos - 1);
				pChannel = new CXDLISChannel(sName);
				m_vecChannel << pChannel;
			}

			if (bFrame)
			{
				pFrame = new CXDLISFrame(sName);
				m_vecFrame << pFrame;
			}
		}
		else
		{
			//	Not object or attribute, seems error!
			m_stream << "Other contents in the LR!" << endl;
			break;
		}
	}

	m_stream << "------------------------------------------------------------------------" <<endl << endl;

	return true;
}