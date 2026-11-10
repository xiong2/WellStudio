#ifndef _CXTemplate_H__
#define _CXTemplate_H__

#include "xdata_global.h"

///@brief	Used to represent a log template.
///@author	Xiong Xiong
///@date	Apr, 2013
///@see		
class XDATA_EXPORT CXTemplate
{
public:
	///	Initialize templates, should be called while app start.
	static bool InitializeTemplates();

	///	Get all availabe templates.
	static QStringList GetAllTemplates();

	///	Get all templates of a specific type.
	static QStringList GetTemplatesOfType(QString sType);

	///	Find the special template by ID.
	static CXTemplate* GetTemplate(unsigned int iID);

	///	Find the special template by ID.
	static QString GetTemplateName(unsigned int iID);

	///	Find the special template by name or alias.
	static CXTemplate* GetTemplate(QString sName);

	///	Get template name.
	QString GetName()
	{
		return m_sName;
	}

	///	Get the ID
	unsigned int GetID()
	{
		return m_iTemplateID;
	}

	///	Get the unit.
	QString GetUnit();

	///	Get the template type.
	QString GetType()
	{
		return m_sType;
	}

	///	Get the icon name.
	QString GetIcon()
	{
		return m_sIcon;
	}

	///	Get the data range.
	virtual void GetDataRange(double& dDataMin, double& dDataMax) = 0;

	///	Get the display range.
	virtual void GetDisplayRange(double& dDspMin, double& dDspMax) = 0;

	///	Whether uses logarithmic scale.
	virtual bool UseLogarithmicScale() = 0;

	virtual bool IsContinuous() = 0;

protected:
	CXTemplate(unsigned int iTemplateID, QString sName, QString sFullName, QString sType, QString sIcon, QString sAlias);

	unsigned int	m_iTemplateID;			//	Unique ID for each template.
	QString			m_sName;				//	Name.
	QString			m_sFullName;			//	Full name.
	QString			m_sType;				//	Type.
	QString			m_sUnitMetric;			//	Metric unit name.
	QString			m_sUnitImperial;		//	Imperial unit name.
	QString			m_sIcon;				//	Icon name.
	QStringList		m_sListAlias;			//	A list of alias.

	static QList<CXTemplate *> m_staListTemplate;
};

class XDATA_EXPORT CXContinuousTemplate : public CXTemplate
{
public:
	static CXContinuousTemplate* CreateContinuousTemplates(unsigned int iTemplateID, QString sName, QString sFullName, QString sType,
		QString sIcon, QString sAlias, QString sUnitM, QString sUnitI,
		double dDataMinM, double dDataMaxM, double dDspMinM, double dDspMaxM,
		double dDataMinI, double dDataMaxI, double dDspMinI, double dDspMaxI, bool bLogarithmicScale);

	virtual bool IsContinuous()
	{
		return true;
	}

	///	Whether uses logarithmic scale.
	virtual bool UseLogarithmicScale()
	{
		return m_bLogarithmicScale;
	}

	///	Get the data range.
	virtual void GetDataRange(double& dDataMin, double& dDataMax);

	///	Get the display range.
	virtual void GetDisplayRange(double& dDspMin, double& dDspMax);

	CXContinuousTemplate(unsigned int iTemplateID, QString sName, QString sFullName, QString sType,
		QString sIcon, QString sAlias, QString sUnitM, QString sUnitI, 
		double dDataMinM, double dDataMaxM, double dDspMinM, double dDspMaxM,
		double dDataMinI, double dDataMaxI, double dDspMinI, double dDspMaxI, bool bLogarithmicScale);

protected:
	double			m_dDataMinMetric;		//	Minimum data value (metric).
	double			m_dDataMaxMetric;		//	Maximum data value (metric).
	double			m_dDspMinMetric;		//	Minimum display value (metric).
	double			m_dDspMaxMetric;		//	Maximum display value (metric).
	double			m_dDataMinImperial;		//	Minimum data value (imperial).
	double			m_dDataMaxImperial;		//	Maximum data value (imperial).
	double			m_dDspMinImperial;		//	Minimum display value (imperial).
	double			m_dDspMaxImperial;		//	Maximum display value (imperial).
	bool			m_bLogarithmicScale;	//	Whether uses logarithmic scale.
};

class XDATA_EXPORT CXDiscreteTemplate : public CXTemplate
{
public:
	static CXDiscreteTemplate* CreateDiscreteTemplate(unsigned int iTemplateID, QString sName, QString sFullName, QString sType,
		QString sIcon, QString sAlias, QString sProperties, QString sColors);

	virtual bool IsContinuous()
	{
		return false;
	}

	///	Whether uses logarithmic scale.
	virtual bool UseLogarithmicScale()
	{
		return false;
	}

	///	Get the data range.
	virtual void GetDataRange(double& dDataMin, double& dDataMax)
	{
		dDataMin = 0.;
		dDataMax = m_sListProperties.size() - 1;
	}

	///	Get the display range.
	virtual void GetDisplayRange(double& dDspMin, double& dDspMax)
	{
		dDspMin = 0.;
		dDspMax = m_sListProperties.size() - 1;
	}

	QStringList& GetAllPropertiesRef()
	{
		return m_sListProperties;
	}

	QList<QColor>& GetAllColorsRef()
	{
		return m_listColor;
	}

protected:
	CXDiscreteTemplate(unsigned int iTemplateID, QString sName, QString sFullName, QString sType,
		QString sIcon, QString sAlias);

	QStringList		m_sListProperties;
	QList<QColor>	m_listColor;
};

#endif