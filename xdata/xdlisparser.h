#ifndef _CXDLISPARSER_H__
#define _CXDLISPARSER_H__

#include <qfile.h>
#include <qtextstream.h>

class CXObject;
class CXWell;

//	For Log Curve channel.
class CXDLISChannel
{
public:
	CXDLISChannel(QString sName)
	{
		m_sName = sName;
		m_sDesp = "";
		m_sUnit = "";
		m_iRepCode = 2;
		m_iDimension = 1;
		m_pBuffer = NULL;
	}

	~CXDLISChannel()
	{
		if (m_pBuffer)
			delete []m_pBuffer;
	}

	QString	m_sName;
	QString m_sDesp;
	QString m_sUnit;
	unsigned char	m_iRepCode;		//	Representation code.
	unsigned int	m_iDimension;	//	The size of the horizontal dimension.
	double*			m_pBuffer;
};

//	For frame
class CXDLISFrame
{
public:
	CXDLISFrame(QString sObjName)
	{
		m_sObjName = sObjName;
	}

	QString	m_sObjName;
	float	m_fSDepth;
	float	m_fEDepth;
	float	m_fSpacing;
	QString	m_sDepthUnit;
	int		m_iNumSamples;
	QStringList					m_listChannel;
	QVector<CXDLISChannel *>	m_vecChannel;
};

//	Component Descriptor
class CXDLISCD
{
public:
	CXDLISCD(unsigned char *);

	int GetType()
	{
		return m_iType;
	}

	//	For attribute: 0 L, 1 C, 2 R, 3 U, 4 V;
	//	For object: 0 N;
	//	For set: 0 T, 1 N;
	bool Contains(int iSymbol);

private:
	//	-1	Not used
	//	0	Absent Attribute
	//	1	Attribute
	//	2	Invariant Attribute
	//	3	Object
	//	4	Redundant Set
	//	5	Replacement Set
	//	6	Set
	int				m_iType;	

	unsigned char*	m_pCh;		//	Source byte.
};

struct SKEDLISLR
{
	qint64			m_iStartPos;
	unsigned int	m_iLength;
};

class CXDLISParser
{
public:
	CXDLISParser(QString sFileName);
	~CXDLISParser();

	bool Parse();

	QString GetWellName()
	{
		return m_strWellName;
	}

	void PopulateCurvesAndUnits(QStringList& sListCurves, QStringList& sListUnits);

	void PopulateWellRange(float& fSDepth, float& fEDepth, float& fDepthStep);

	bool LoadCurves(CXWell *pWell, QStringList& sListCurves, QList<CXObject *>& listObj);

private:
	void readVRHeader();

	//	Convenient functions.
	void flipShort(char *pSh, int iNum = 1);
	void flip4Bytes(char *pCh, int iNum = 1);

	float readFSINGL(unsigned char *&);				//	RepCode 2
	short readSNORM(unsigned char *&);				//	RepCode 13
	int readSLONG(unsigned char *&);				//	RepCode 14
													//	RepCode 15/26 read directly.
	unsigned short readUNORM(unsigned char *&);		//	RepCode 16
	unsigned int readULONG(unsigned char *&);		//	RepCode 17
	unsigned int readUVARI(unsigned char *&);		//	RepCode 18/22
	QString readIDENT(unsigned char *&);			//	RepCode 19/27
	QString readASCII(unsigned char *&);			//	RepCode 20
	QString readDTIME(unsigned char *&);			//	RepCode 21
	QString readOBNAME(unsigned char *&);			//	RepCode 23
	QString readOBJREF(unsigned char *&);			//	RepCode 24
	QString readRepCode(unsigned char *&, unsigned char repCode);

	bool parseEFLR(unsigned char *pBuff, int iLength, unsigned char iType);		//	Parse one EFLR, may multiple segments.
	bool parseIFLR(unsigned char *pBuff, int iLength);				//	Parse one IFLR, one segment each time.

	bool readCD();						//	Read 1 byte CD, Component Descriptor.

	//	After reading all CHANNEL and FRAME LR, sort all channels to data order.
	void sortChannels();

	QFile			m_qDLISFile;	
	QFile			m_qTXTFile;
	QTextStream		m_stream;

	int				m_iCurVRLen;		//	Lenght of current visible record.
	int				m_iCurLRSLen;		//	Length of current logcial record segment.
	qint64			m_iNextVRPos;		//	Start position of next visible record.
	qint64			m_iNextLRSPos;		//	Start position of next logical record segment.

	QStringList					m_listSChannelName;		//	List of channels' name in FRAME segment.
	QVector<CXDLISChannel *>	m_vecChannel;			//	Vector of channels parsed from CHANNEL segment.
	QVector<CXDLISFrame *>		m_vecFrame;				//	Vector of frame parsed from FRAME segment.

	QString			m_strWellName;
};

#endif