#ifndef XASCIIFILE_H
#define XASCIIFILE_H

#include "xdata_global.h"
#include "xdelimiter.h"
#include "xdef.h"

#define MAXLINENUMBER 30000000

///@brief	Used to represent an ASCII file being imported.
///@author	Xiong Xiong
///@date	Apr, 2013
///@see		
class XDATA_EXPORT CXASCIIFile
{
public:
	CXASCIIFile(EImportFileType eFileType = eGeneralASCII, QString sFile = "");
    virtual ~CXASCIIFile();

	///	Set file.
	bool SetFile(QString sFile, QString sObjName = "");

	///	Get the file name.
	const QString& GetFileName()
	{
		return m_sFile;
	}

	qint64 GetLineNumber()
	{
		return m_iLineNumber;
	}

	double GetInvalid()
	{
		return m_dInvalid;
	}

	void SetInvalid(double dInv)
	{
		m_dInvalid = dInv;
	}

	unsigned int GetImportFrom()
	{
		return m_iImportFrom;
	}

	void SetImportFrom(unsigned int iFrom)
	{
		m_iImportFrom = iFrom < m_iLineNumber ? iFrom : m_iLineNumber;
	}

	qint64 GetImportTo()
	{
		return m_iImportEnd;
	}

	void SetImportTo(qint64 iTo)
	{
		m_iImportEnd = iTo < m_iLineNumber ? iTo : m_iLineNumber;
	}

	CXDelimiter*& GetDelimiter()
	{
		return m_pDelimiter;
	}

	unsigned int GetNameLine()
	{
		return m_iNameLine;
	}

	void SetNameLine(unsigned int iNameLine)
	{
		m_iNameLine = iNameLine;
	}

	unsigned int GetPreviewLineNumber()
	{
		return m_iPreviewLineNumber;
	}

	void SetPreviewLineNumber(unsigned int iPreviewLineNumber)
	{
		m_iPreviewLineNumber = iPreviewLineNumber;
	}

	///	Get the candidates for each column.
	QStringList& GetColumnCandidates()
	{
		return m_sListColumnCandidates;
	}

	///	Get the chosen columns, notes it's writable.
	QStringList& GetChosenColumns()
	{
		return m_sListColumnChosen;
	}

	///	Static feature to find out the line number of an ASCII file.
	static qint64 GetASCIIFileLineNumber(QString sFile);

	///@brief	Get attributes' name, notes its writable.
	QStringList& GetAttributes()
	{
		return m_sListAttributes;
	}

	///@brief	Get attributes' data type, notes its writable.
	QList<int>& GetAttributeDataType()
	{
		return m_iListDataType;
	}

	///@brief	Get attributes' unit convert ratio, notes its writable.
	QList<float>& GetAttributeUnitRatio()
	{
		return m_fListUnitRatio;
	}

	///@brief	Get file type.
	EImportFileType GetFileType()
	{
		return m_eFileType;
	}

	///@brief	Let derived classes to check the selected columns.
	virtual bool CheckSelectedColumns(QStringList&)
	{
		return true;
	}

	///@brief	Import, need be implemented by derived classes.
	virtual bool Import() = 0;

	///@brief Set the object name
	void SetOjectName(const QString& strObjName) {m_sObjName = strObjName;}
	QString GetObjectName() { return m_sObjName; }

	///@brief	Whether import to file end.
	void ImportToFileEnd(bool bEOF = true)
	{
		m_bEOF = bEOF;
	}

	EDomainType GetDomainType() const { return m_eDomainType; }
	void SetDomainType(EDomainType eDomainType) { m_eDomainType = eDomainType; }

	///@brief	Get each column's name using the specific line.
	QStringList GuessColumnName();

protected:
	EImportFileType	m_eFileType;				//	File type.
	QString			m_sFile;					//	Name of the ASCII file.
	QString			m_sObjName;					//	Target object name.
	qint64			m_iLineNumber;				//	Line number of the file.
	double			m_dInvalid;					//	Invalid value used in this file.
	unsigned int	m_iImportFrom;				//	From which line to import.
	qint64			m_iImportEnd;				//	The end line number to be imported.
	CXDelimiter*	m_pDelimiter;				//	A delimiter.
	bool			m_bEOF;						//	Whether import to file end.
	unsigned int	m_iNameLine;				//	From which line to guess the column name.
	unsigned int	m_iPreviewLineNumber;		//	How many lines to preview.
	QStringList		m_sListColumnCandidates;	//	A list of candidates for column.
	QStringList		m_sListColumnChosen;		//	A list of chosen columns.
	QStringList		m_sListAttributes;			//	List of attributes' name, chosen columns exclude "Do not import".
	QList<int>		m_iListDataType;			//	List of attirbutes' data type.
	QList<float>	m_fListUnitRatio;			//	List of attributes' unit convert ratio.
	EDomainType		m_eDomainType;				//	Domain type.
};

#endif // RLASCIIFILE_H
