#ifndef _KELASWISFILE_H__
#define _KELASWISFILE_H__

#include "xdata_global.h"

#include <QFile>
#include <qtextstream.h>

class CXWell;
class CXObject;
class CXDLISParser;

///@brief	Used to represent an LAS file being imported.
///@author	Xiong Xiong
///@date	Apr, 2013
///@see		
class XDATA_EXPORT CXLasWisFile
{
public:
	CXLasWisFile(QString sFile, int iFileType = 0);
	~CXLasWisFile();

	///	Parse the file to extract basic well informatoin.
	bool ParseFile();

	///	Load curves stored in the file.
	bool LoadCurves(QStringList& listCurves, QList<CXObject *>&);

	QString GetFileName(bool bNoPath = false);

	CXWell* GetWell()
	{
		return m_pWell;
	}

	void SetWell(CXWell *pWell)
	{
		m_pWell = pWell;
	}

	QStringList& GetCurveList()
	{
		return m_sListCurves;
	}

	QStringList& GetUnitList()
	{
		return m_sListUnits;
	}

protected:
	int				m_iFileType;		//	0 LAS, 1 WIS, 2 XTF, 3 DLIS.
	QString			m_sFileName;		//	File name.
	CXWell*		m_pWell;			//	Hold a well.
	float			m_dStart;			//	Start of the well.
	float			m_dStop;			//	Stop of the well.
	float			m_dStep;			//  Step of the well.
	QString			m_sDepthUnit;		//	Unit of depth.
	QString			m_sDelimiter;		//	Delimiter.
	float			m_dInvalid;			//	Invalid value in this file.
	QFile			m_qFile;			//	The handle of the QFile.
	QTextStream		m_qStream;			//	The handle of the text stream.

	bool			m_bWrapped;			//	Whether uses multiple lines for one depth;

	QStringList		m_sListCurves;		//	List of curve name.
	QStringList		m_sListUnits;		//	List of unit each curve used.
	QVector<int>	m_vecOffset;		//	Used by WIS and XTF.

	CXDLISParser*	m_pDLISParser;

	bool parseLASFile();
	bool loadLASCurves(QStringList& listCurves, QList<CXObject *>&);

	bool parseWISFile();
	bool loadWISCurves(QStringList& listCurves, QList<CXObject *>&);

	bool parseXTFFile();
	bool loadXTFCurves(QStringList& listCurves, QList<CXObject *>&);

	bool parseDLISFile();
	bool loadDLISCurves(QStringList& listCurves, QList<CXObject *>&);

	//	Get the name from the line, name before the first "."
	QString getName(QString sLine);

	//	Get the value from the line, value between ".unit " and ":".
	QString getValue(QString sLine);

	//	Get the unit from the line, unit just after the 1st ".".
	QString getUnit(QString sLine);
};

#endif