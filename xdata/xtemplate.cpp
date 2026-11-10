#include <QtSql>
#include <qdebug.h>

#include "xtemplate.h"
#include "xglobal.h"
#include "xlog.h"
#include "xdbio.h"

QList<CXTemplate *> CXTemplate::m_staListTemplate;

bool CXTemplate::InitializeTemplates()
{
	//  Prepare the database first.
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(CXDBIO::GetTemplateFileName());

    if(!db.open())
    {
		CXLog::AddLog("Open DB error: " + CXDBIO::GetTemplateFileName());
        qDebug()<<db.lastError();
        return false;
    }

	m_staListTemplate.clear();

	QSqlQueryModel model;
	model.setQuery("SELECT * FROM Continuous");
	for(int i = 0; i < model.rowCount(); i++)
	{
		m_staListTemplate << CXContinuousTemplate::CreateContinuousTemplates(
			model.record(i).value("ID").toUInt(),
			model.record(i).value("Name").toString(),
			model.record(i).value("FullName").toString(),
			model.record(i).value("Type").toString(),
			model.record(i).value("Icon").toString(),
			model.record(i).value("Alias").toString(),
			model.record(i).value("MetricUnit").toString(),
			model.record(i).value("ImperialUnit").toString(),
			model.record(i).value("DataMinMetric").toDouble(), 
			model.record(i).value("DataMaxMetric").toDouble(),
			model.record(i).value("DisplayMinMetric").toDouble(), 
			model.record(i).value("DisplayMaxMetric").toDouble(),
			model.record(i).value("DataMinImperial").toDouble(), 
			model.record(i).value("DataMaxImperial").toDouble(),
			model.record(i).value("DisplayMinImperial").toDouble(), 
			model.record(i).value("DisplayMaxImperial").toDouble(),
			model.record(i).value("LogarithmicScale").toBool());
	}

	model.setQuery("SELECT * FROM Discrete");
	for (int i = 0; i != model.rowCount(); ++i)
	{
		m_staListTemplate << CXDiscreteTemplate::CreateDiscreteTemplate(
			model.record(i).value("ID").toUInt(),
			model.record(i).value("Name").toString(),
			model.record(i).value("FullName").toString(),
			model.record(i).value("Type").toString(),
			model.record(i).value("Icon").toString(),
			model.record(i).value("Alias").toString(),
			model.record(i).value("Properties").toString(),
			model.record(i).value("Colors").toString());
	}

	std::sort(std::next(m_staListTemplate.begin()), m_staListTemplate.end(), [](CXTemplate* t1, CXTemplate* t2)
	{
		return t1->GetName() < t2->GetName();
	});

	return true;
}

//	Get all availabe templates.
QStringList CXTemplate::GetAllTemplates()
{
	QStringList sList;
	int i, iSize = m_staListTemplate.size();

	for(i = 0; i < iSize; i++)
	{
		sList<<m_staListTemplate[i]->m_sName;
	}

	return sList;
}

//	Get all templates of a specific type.
QStringList CXTemplate::GetTemplatesOfType(QString sType)
{
	QStringList sList;
	int i, iSize = m_staListTemplate.size();

	for(i = 0; i < iSize; i++)
	{
		if(m_staListTemplate[i]->m_sType == sType)
			sList<<m_staListTemplate[i]->m_sName;
	}

	return sList;
}

//	Find the special template by name or alias.
CXTemplate* CXTemplate::GetTemplate(QString sName)
{
	int i, iSize = m_staListTemplate.size();

	for(i = 0; i < iSize; i++)
	{
		if(m_staListTemplate[i]->m_sName == sName || m_staListTemplate[i]->m_sListAlias.contains(sName, Qt::CaseInsensitive))
		{
			return m_staListTemplate[i];
		}
	}

	//	If not found, return the 1st one, which is the GENERAL.
	return m_staListTemplate[0];
}

//	Find the special template by ID.
CXTemplate* CXTemplate::GetTemplate(unsigned int iID)
{
	int i, iSize = m_staListTemplate.size();

	for (i = 0; i < iSize; i++)
	{
		if (m_staListTemplate[i]->m_iTemplateID == iID)
		{
			return m_staListTemplate[i];
		}
	}

	//	If not found, return the 1st one, which is the GENERAL.
	return m_staListTemplate[0];
}

//	Find the special template by ID.
QString CXTemplate::GetTemplateName(unsigned int iID)
{
	int i, iSize = m_staListTemplate.size();

	for (i = 0; i < iSize; i++)
	{
		if (m_staListTemplate[i]->m_iTemplateID == iID)
		{
			return m_staListTemplate[i]->GetName();
		}
	}

	//	If not found, return the 1st one, which is the GENERAL.
	return "GENERAL";
}

//	Get the unit.
QString CXTemplate::GetUnit()
{
	if(::UsingMetricUnit())
		return m_sUnitMetric;
	else
		return m_sUnitImperial;
}

CXTemplate::CXTemplate(unsigned int iID, QString sName, QString sFullName, QString sType, QString sIcon, QString sAlias)
{
	m_iTemplateID = iID;
	m_sName = sName;
	m_sFullName = sFullName;
	m_sType = sType;
	m_sIcon = sIcon;
	m_sListAlias = sAlias.split(",");
}

CXContinuousTemplate::CXContinuousTemplate(unsigned int iID, QString sName, QString sFullName, QString sType,
	QString sIcon, QString sAlias, QString sUnitM, QString sUnitI, 
	double dDataMinM, double dDataMaxM, double dDspMinM, double dDspMaxM, 
	double dDataMinI, double dDataMaxI, double dDspMinI, double dDspMaxI, bool bLogarithmicScale)
	: CXTemplate(iID, sName, sFullName, sType, sIcon, sAlias)
{
	m_sUnitMetric		= sUnitM;
	m_sUnitImperial		= sUnitI;
	m_dDataMinMetric	= dDataMinM;
	m_dDataMaxMetric	= dDataMaxM;
	m_dDspMinMetric		= dDspMinM;
	m_dDspMaxMetric		= dDspMaxM;
	m_dDataMinImperial	= dDataMinI;
	m_dDataMaxImperial	= dDataMaxI;
	m_dDspMinImperial	= dDspMinI;
	m_dDspMaxImperial	= dDspMaxI;
	m_bLogarithmicScale	= bLogarithmicScale;
}

CXContinuousTemplate * CXContinuousTemplate::CreateContinuousTemplates(unsigned int iTemplateID, QString sName, QString sFullName, QString sType, QString sIcon, QString sAlias, QString sUnitM, QString sUnitI, double dDataMinM, double dDataMaxM, double dDspMinM, double dDspMaxM, double dDataMinI, double dDataMaxI, double dDspMinI, double dDspMaxI, bool bLogarithmicScale)
{
	return new CXContinuousTemplate(iTemplateID, sName, sFullName, sType, sIcon, sAlias, sUnitM, sUnitI, dDataMinM, dDataMaxM, dDspMinM, dDspMaxM, dDataMinI, dDataMaxI, dDspMinI, dDspMaxI, bLogarithmicScale);
}

//	Get the data range.
void CXContinuousTemplate::GetDataRange(double& dDataMin, double& dDataMax)
{
	if (::UsingMetricUnit())
	{
		dDataMin = m_dDataMinMetric;
		dDataMax = m_dDataMaxMetric;
	}
	else
	{
		dDataMin = m_dDataMinImperial;
		dDataMax = m_dDataMaxImperial;
	}
}

//	Get the display range.
void CXContinuousTemplate::GetDisplayRange(double& dDspMin, double& dDspMax)
{
	if (::UsingMetricUnit())
	{
		dDspMin = m_dDspMinMetric;
		dDspMax = m_dDspMaxMetric;
	}
	else
	{
		dDspMin = m_dDspMinImperial;
		dDspMax = m_dDspMaxImperial;
	}
}

CXDiscreteTemplate * CXDiscreteTemplate::CreateDiscreteTemplate(unsigned int iTemplateID, QString sName, QString sFullName, QString sType, QString sIcon, QString sAlias, QString sProperties, QString sColors)
{
	auto pTemplate = new CXDiscreteTemplate(iTemplateID, sName, sFullName, sType, sIcon, sAlias);
	QList<QColor>& listColors = pTemplate->GetAllColorsRef();

	pTemplate->GetAllPropertiesRef() = sProperties.split(',');
	listColors.clear();
	for (auto strColor : sColors.split(','))
	{
		listColors << QColor(strColor.toUInt());
	}

	return pTemplate;
}

CXDiscreteTemplate::CXDiscreteTemplate(unsigned int iID, QString sName, QString sFullName, QString sType, QString sIcon, QString sAlias)
	: CXTemplate(iID, sName, sFullName, sType, sIcon, sAlias)
{
}