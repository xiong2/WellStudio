#ifndef _CXDELIMITER_H__
#define _CXDELIMITER_H__

#include <qstringlist.h>

#include "xbasic_global.h"

///@brief	Used to parese one string line into data segments according to delimiters.
///@author	Xiong Xiong
///@date	Apr, 2013
///@see		
class XBASIC_EXPORT CXDelimiter
{
public:
	CXDelimiter(QString sDefaultDelimiter = " ");

	///	Update standard delimiter.
	void UpdateDelimiter(QString sDelimiter, bool bAdd);

	///	Get all delimiters.
	QStringList GetAllStandardDelimiters()
	{
		return m_sListDelimiter;
	}

	///	Set the user defined delimiter.
	void ChangeUserDefinedDelimiter(QString sDelimiter)
	{
		m_sUserDefinedDelimiter = sDelimiter;;
	}

	///	Get user defined delimiter.
	QString GetUserDefinedDelimiter()
	{
		return m_sUserDefinedDelimiter;
	}

	///	Allow blank item as result?
	void AllowBlankItem(bool bAllowBlankItem)
	{
		m_bAllowBlankItem = bAllowBlankItem;
	}

	bool IsAllowBlankItem()
	{
		return m_bAllowBlankItem;
	}

	///	Get the using quotes.
	QString GetUsingQuotes(bool& bDouble, bool& bSingle, bool& bUserDefined)
	{
		bDouble = m_bDoubleQuotes;
		bSingle = m_bSingleQuotes;
		bUserDefined = m_bUserDefinedQuotes;

		return m_sUserDefinedQuotes;
	}

	///	Use double quotes.
	void UseDoubleQuotes(bool bUse)
	{
		m_bDoubleQuotes = bUse;
	}

	///	Use single quotes.
	void UseSingleQuotes(bool bUse)
	{
		m_bSingleQuotes = bUse;
	}

	void UseUserDefinedQuotes(bool bUse)
	{
		m_bUserDefinedQuotes = bUse;
	}

	///	Use user defined quotes.
	void UseUserDefinedQuotes(QString sUserDefinedQuotes)
	{
		m_sUserDefinedQuotes = sUserDefinedQuotes;
	}

	///	Get the splitted data segments of the given line.
	QStringList GetSplittedString(QString sLine);

protected:
	QStringList		m_sListDelimiter;			//	A list of delimiter.
	QString			m_sUserDefinedDelimiter;	//	User defined delimiter.
	bool			m_bAllowBlankItem;			//	Whether allow blank item exist.
	bool			m_bDoubleQuotes;			//	Using double quotes.
	bool			m_bSingleQuotes;			//	Using single quotes.
	bool			m_bUserDefinedQuotes;		//	Using user defined quotes.
	QString			m_sUserDefinedQuotes;		//	Using user defined quotes.
};

#endif