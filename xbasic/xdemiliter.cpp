#include "xdelimiter.h"
#include "xlog.h"

CXDelimiter::CXDelimiter(QString sDelimiter)
{
	if(sDelimiter != "")
		m_sListDelimiter<<sDelimiter;

	m_bAllowBlankItem		= false;
	m_bDoubleQuotes			= false;
	m_bSingleQuotes			= false;
	m_bUserDefinedQuotes	= false;

}

//	Update standard delimiter.
void CXDelimiter::UpdateDelimiter(QString sDelimiter, bool bAdd)
{
	//	Only 5 standard delimiters are allowed.
	if(sDelimiter != " " && sDelimiter != "\t" && sDelimiter != ","
		&& sDelimiter != ":" && sDelimiter != ";")
		return;

	if(!m_sListDelimiter.contains(sDelimiter, Qt::CaseInsensitive) && bAdd)
		m_sListDelimiter<<sDelimiter;

	if(m_sListDelimiter.contains(sDelimiter, Qt::CaseInsensitive) && !bAdd)
		m_sListDelimiter.removeAll(sDelimiter);
}

//	Get the splitted data segments of the given line.
QStringList CXDelimiter::GetSplittedString(QString sLine)
{
	int i, j, iIDX1, iIDX2;
	QStringList sListQuotesContents, sListQuotes;

	//	Prepare quotes.
	if(m_sUserDefinedQuotes != "")
		sListQuotes<<m_sUserDefinedQuotes;
	if(m_bDoubleQuotes)
		sListQuotes<<"\"";
	if(m_bSingleQuotes)
		sListQuotes<<"\'";

	for(i = 0; i < sListQuotes.size(); i++)	
	{
		QString sQuotes = sListQuotes.at(i);
		int iLen = sQuotes.size();
		while(sLine.indexOf(sQuotes) != -1)
		{
			//	Remove the left quotes.
			iIDX1 = sLine.indexOf(sQuotes);
			sLine.remove(iIDX1, iLen);

			//	Remove the right quotes.
			iIDX2 = sLine.indexOf(sQuotes);
			if(iIDX2 == -1)
				break;
			sLine.remove(iIDX2, iLen);

			//	Replace the contents between the quotes.
			QString strTmp = sLine.mid(iIDX1, (iIDX2 - iIDX1));
			sLine.replace(iIDX1, (iIDX2 - iIDX1), "$#$#$" + QString::number(sListQuotesContents.size()) + "$#$#$");
			sListQuotesContents<<strTmp;
		}
	}

	//	Now let's splite it, merge the user defined delimiter first.
	if(m_sUserDefinedDelimiter != "")
		m_sListDelimiter<<m_sUserDefinedDelimiter;
	
	QStringList sList, sListTmp, sListContainer;

	//	Initialize the list.
	sListContainer<<sLine;

	//	Loop to use each delimiter.
	for(i = 0; i < m_sListDelimiter.size(); i++)
	{
		sList = sListContainer;
		sListContainer.clear();

		for(j = 0; j < sList.size(); j++)
		{
			sListTmp = sList.at(j).split(m_sListDelimiter.at(i));
			sListContainer += sListTmp;
		}
	}

	//	Wipe out the user defined delimiter from the list.
	if(m_sUserDefinedDelimiter != "")
		m_sListDelimiter.removeOne(m_sUserDefinedDelimiter);

	//	Now copy back what included in the quotes.
	for(i = 0; i < sListContainer.size(); i++)
	{
		QString sData = sListContainer.at(i);
		if(sListContainer.at(i).contains("$#$#$"))
		{
			while(sData.indexOf("$#$#$") != -1)
			{
				//	Wipe out the left-right specific delimiter first.
				iIDX1 = sData.indexOf("$#$#$");
				sData.remove(iIDX1, 5);
				iIDX2 = sData.indexOf("$#$#$");
				if(iIDX2 == -1)
				{
					CXLog::AddLog("Something wrong while splitting string, the quoteses are not matched!");
					CXLog::AddLog("The string is: " + sData);
					break;
				}
				sData.remove(iIDX2, 5);

				int iIDX = sData.mid(iIDX1, (iIDX2 - iIDX1)).toInt();
				if(iIDX >= sListQuotesContents.size())
				{
					CXLog::AddLog("Something wrong whiel splitting string, stored contents within quotes wrong!");
					CXLog::AddLog("The string is: " + sData);
					break;
				}
				sData.replace(iIDX1, (iIDX2 - iIDX1), sListQuotesContents.at(iIDX));
			}

			sListContainer.replace(i, sData);
		}
	}

	//	Whether allow blank items.
	if(!m_bAllowBlankItem)
	{
		sListContainer.removeAll("");
	}

	return sListContainer;
}