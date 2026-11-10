#ifndef _CXUNIT_H__
#define _CXUNIT_H__

#include <vector>
#include <qstringlist.h>

#include "xbasic_global.h"

///@brief	Define the type of units.  Units of the same type could be mutual converted.
///@brief	Each unit type has a standard unit, used for unit convertion, which given in the comments.
enum EXUnitType
{
	eVoid,				//	No unit.
	eTime,				//	Time, e.g. ms.
	eLength,			//	Length, e.g. m.
	eArea,				//	Area, e.g. m2.
	eVolume,			//	Volume, e.g. m3.
	eWeight,			//	Weight, e.g. kg.
	eGammaRay,			//	For gamma ray, e.g. API.
	ePotential,			//	For SP, e.g. mV.
	ePorosity,			//	For Porosity, e.g. %.
	eDensity,			//	For density, e.g. kg/m3.
	ePhotoelectric,		//	For photoelectric absorption index, e.g. ba/e.
	eTransitTime,		//	For sonic log, e.g. us/m.
	eResistivity,		//	For resistivity log, e.g. ohm.m.
	eGammaRaySpectral,	//	For natuarl gamma-ray spectral logging, e.g. ppm.
	eAngle,				//	Degree.
};

class XBASIC_EXPORT CXUnit
{
public:
	///	Get the name of unit types.
	static QStringList GetAllUnitType();
	
	///	Get the standard unit name of the oriName, if not found return "".
	static QString GetStandardName(QString sOriName);

	///	Get the type of the special unit.
	static EXUnitType GetUnitType(QString sUnit);

	///	Get all available units of the specified type
	static QStringList GetAllUnits(EXUnitType eType);

	///	Get the convert ratio.
	static double GetConvertRatio(QString sSourceUnit, QString sDestinateUnit);

protected:
	EXUnitType		m_eUnitType;		//	Which type this unit is.
	QString			m_sName;			//	Name of the unit, e.g. m.
	QString			m_sFullName;		//	Full name of the unit, e.g. meter.
	QStringList		m_listSAlias;		//	A list of alias.
	double			m_dRatio;			//	The ratio used to convert to the standard one.

	//	Protectd constructor.
	CXUnit(EXUnitType eType, QString sName, QString sFullName = "", double fRatio = 1.);

	//	Get the static unit vector
	static std::vector<CXUnit>& getUnitVector();
};

#endif